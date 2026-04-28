#include "LevelWithTiles.h"

LevelWithTiles::LevelWithTiles(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio)
	: Scene(window, input, gameState, audio), m_alertText(m_font), m_pauseScene(window, input, gameState, audio)
{
	
	loadtile();
	loadBG();

	// setup player 
	m_player.setPosition({ 100, 300 });
	m_player.getFillColor() = sf::Color::Green;
	m_player.setInput(&m_input);
	m_player.setEdges(0, WORLD_SIZE.x);

	//m setup text
	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";
	m_alertText.setString("Who keeps turning\nthe wind off?");
	m_alertText.setPosition({ 50, 150});
	m_alertText.setCharacterSize(36);
	m_alertText.setFillColor(sf::Color::Black);
	m_promptTimer = PROMPT_TIME;
	if (!m_tileTexture.loadFromFile("gfx/tilemap.png")) std::cerr << "no tile image found";

	// setup flags and end game pos
	m_player.setEndGamePosition({ 24, 325 });
	for (int i = 0; i < 3; i++)
	{
		Flag* new_flag = new Flag();
		new_flag->setSize({ 72,72 });
		new_flag->setPosition({72.f + (i * 288), 100.f});
		new_flag->setTexture(&m_tileTexture);
		new_flag->setup();	// ensure first frame is good.
		m_flags.push_back(new_flag);
	}

	m_lever.setPosition({ 2730, 252 });
	m_lever.setTexture(&m_tileTexture);
	m_lever.setSize({ 72,72 });
	m_lever.setUsed(false);
	m_player.setLeverPosition({ 2730, 252 });
	m_player.setAudio(&m_audio);
}

//load ground tiles for lv1
void LevelWithTiles::loadtile() {
	GameObject tile;
	std::vector<GameObject> tileset;
	std::ifstream tileSets("data/groundTile1.txt");  // "C:\Users\HP\source\repos\Magi-Dino\Coursework\CMP105App\data\tileLv1.txt"
	std::vector<int> tileLocation = {};
	if (!tileSets.is_open()) { std::cout << "WHY?? NO TILES\n"; }
	std::string tileData;
	int num_columns = 20;
	int num_rows = 9;
	int tile_size = 18;      // Visual size of the tile
	int sheet_spacing = 1;   // Gap between tiles


	// Set GameObject size (Scaling up 4x for visibility)
	// 4 * 18 = 3 * 24 = 72 (dino size is 24).
	tile.setSize(sf::Vector2f(tile_size * 4, tile_size * 4));
	tile.setCollisionBox({ { 0,0 }, tile.getSize() });

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;

		tile.setTextureRect({
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
			{tile_size, tile_size} });
		if (col <= 4 || col >= 12) tile.setCollider(true);
		else tile.setCollider(false);
		tileset.push_back(tile);
	}

	// Add Blank
	tile.setTextureRect({ {0, 0}, {-24, -24} }); // Empty rect for blank
	m_blank = tileset.size();
	tile.setCollider(false);
	tileset.push_back(tile);
	sf::Vector2u mapDimensions{ 40, 8 };


	while (tileSets >> tileData) {
		std::cout << tileData << ", Doing the tiles\n";

		//find comma in file and delete comma prevent stoi error
		int pos = tileData.find(",");
		std::string blanktiles = tileData.substr(0, pos);

		if (blanktiles == "b") {
			tileLocation.push_back(m_blank);
		}
		else {
			int tiles = stoi(tileData);
			tileLocation.push_back(tiles);
		}
	}
	m_tilemap.loadTexture("gfx/tilemap.png");
	m_tilemap.setTileSet(tileset);
	m_tilemap.setTileMap(tileLocation, mapDimensions);
	m_tilemap.setPosition({ 0, 100 });
	m_tilemap.buildLevel();

	tileset.clear();

}

//load background tiles for lv1
void LevelWithTiles::loadBG() {
	GameObject tile;
	std::vector<GameObject> tileset;
	std::ifstream tileSets("data/BG1.txt");
	std::vector<int> tileLocation = {};
	if (!tileSets.is_open()) { std::cout << "WHY?? NO TILES\n"; }
	std::string tileData;
	int tile_size = 24;
	int num_columns = 8;
	int num_rows = 3;
	int sheet_spacing = 1;

	tile.setSize(sf::Vector2f(tile_size * 9, tile_size * 9));

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;

		tile.setTextureRect({
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
		{tile_size, tile_size} });
	tile.setCollider(false);		// don't collide with background
		tileset.push_back(tile);
	}
	sf::Vector2u mapDimensions = { 14,3 };

	while (tileSets >> tileData) {
		std::cout << tileData << ", Doing the tiles\n";
		//find comma in file and delete comma prevent stoi error
		int pos = tileData.find(",");
		std::string blanktiles = tileData.substr(0, pos);

		if (blanktiles == "b") {
			tileLocation.push_back(m_blank);
		}
		else {
			int tiles = stoi(tileData);
			tileLocation.push_back(tiles);
		}
	}
	m_bgtilemap.loadTexture("gfx/tilemap-backgrounds.png");
	m_bgtilemap.setTileSet(tileset);
	m_bgtilemap.setTileMap(tileLocation, mapDimensions);
	m_bgtilemap.setPosition({ 0, 0 });
	m_bgtilemap.buildLevel();

	// setup player 
	m_player.setPosition({ 100, 300 });
	m_player.getFillColor() = sf::Color::Green;

	m_player.setInput(&m_input);
	m_player.setEdges(0, WORLD_SIZE.x);

	//set enemy
	

	//m setup text
	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";
	m_alertText.setString("Who keeps turning\nthe wind off?");
	m_alertText.setPosition({ 50, 150});
	m_alertText.setCharacterSize(36);
	m_alertText.setFillColor(sf::Color::Black);
	m_promptTimer = PROMPT_TIME;
	if (!m_tileTexture.loadFromFile("gfx/tilemap.png")) std::cerr << "no tile image found";

	// setup flags and end game pos
	m_player.setEndGamePosition({ 24, 325 });
	for (int i = 0; i < 3; i++)
	{
		Flag* new_flag = new Flag();
		new_flag->setSize({ 72,72 });
		new_flag->setPosition({72.f + (i * 288), 100.f});
		new_flag->setTexture(&m_tileTexture);
		new_flag->setup();	// ensure first frame is good.
		m_flags.push_back(new_flag);
	}

	m_lever.setPosition({ 2730, 252 });
	m_lever.setTexture(&m_tileTexture);
	m_lever.setSize({ 72,72 });
	m_lever.setUsed(false);
	m_player.setLeverPosition({ 2730, 252 });
	m_player.setAudio(&m_audio);
}

void LevelWithTiles::handleInput(float dt)
{
	if(m_pauseScene.getPauseState() == false)
	{
		m_player.handleInput(dt);

		if (m_input.isPressed(sf::Keyboard::Scancode::Escape))
			m_gameState.setCurrentState(State::MENU);
	}
	
	if (m_input.isPressed(sf::Keyboard::Scancode::P)) {
		m_gameState.setCurrentState(State::PAUSE);
		m_pauseScene.handleInput(dt);
	}
	
}

void LevelWithTiles::update(float dt)
{
	if (m_pauseScene.getPauseState() == true)
	{
		return;
	}

	if (m_flagLeverPulled)
	{
		for (auto& flag : m_flags) flag->update(dt);
	}
	m_lever.update(dt);


	//make ref from projectile vector in player
	auto& bullet = m_player.getFired();
	auto& enemies = m_enemy;
	

	for (auto eye = enemies.begin(); eye != enemies.end();) {

		(*eye)->collisionResponse(m_player);
		(*eye)->update(dt);

		if ((*eye)->isAlive() == false) {
			delete (*eye);
			eye = enemies.erase(eye);

		}
		else ++eye;

	}

	for (auto projectile = bullet.begin(); projectile != bullet.end();) {
		(*projectile)->update(dt);
		for(auto& eye : m_enemy)
			(*projectile)->collisionResponse(*eye);
	

		if (!(*projectile)->isAlive()) {
			delete (*projectile);
			projectile = bullet.erase(projectile);

		}
		else ++projectile;

	}
	

	m_player.update(dt);


	std::vector<GameObject>& level = *m_tilemap.getLevel();
	for (auto& t : level)
	{
		if (t.isCollider() && Collision::checkBoundingBox(m_player, t))
		{
			m_player.collisionResponse(t);
		}
	}
	
	// show text if player has dropped very low down
	if (m_promptTimer > 0)
		m_promptTimer -= dt;
	else if (m_alertText.getString() != "")
	{
		// turn off prompt
		m_alertText.setString("");
	}
	else if (m_player.getPosition().y > WORLD_SIZE.y)
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(m_window.getView().getCenter());
		m_alertText.setString("Press R to reset");
	}
	// show text if the player in lever range
	else if (m_player.inLeverRange())
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(m_window.getView().getCenter() + sf::Vector2f(-100.f, -150.f));
		m_promptTimer = PROMPT_TIME;
		if (!m_flagLeverPulled)
			m_alertText.setString("Press F to fix\nthe wind");
		else
			m_alertText.setString("Better check\nthose flags");
	}
	else if (m_player.inEndRange())
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(m_window.getView().getCenter() + sf::Vector2f(-100.f, -150.f));
		m_promptTimer = PROMPT_TIME;
		if (m_flagLeverPulled)
			m_alertText.setString("Good job! Press\nF to end the day");
	}

	if (m_player.getLeverPulled())
	{
		if (!m_flagLeverPulled) m_promptTimer = 0;
		m_flagLeverPulled = true;
		m_lever.setUsed(true);
	}
	else
	{
		m_lever.setUsed(false);
	}
	if (m_player.getGameEndTriggered())
	{
		
		m_gameState.setCurrentState(State::MENU);
	}


	// reset if fallen too far
	if (m_player.getPosition().y > 1200||m_player.getDeath()==true)
	{
		m_player.reset();
		m_audio.playSoundbyName("death");
	}

	// camera follows player, bounded.
	updateCameraAndBackground();

}

void LevelWithTiles::updateCameraAndBackground()
{
	auto view = m_window.getView();
	auto player_pos = m_player.getPosition() + m_player.getSize() * 0.5f;

	float halfViewWidth = VIEW_SIZE.x / 2.0f;
	float halfViewHeight = VIEW_SIZE.y / 2.0f;

	player_pos.x = std::clamp(player_pos.x, halfViewWidth, WORLD_SIZE.x - halfViewWidth);
	player_pos.y = std::clamp(player_pos.y, halfViewHeight, WORLD_SIZE.y - halfViewHeight);

	view.setCenter(player_pos);
	m_window.setView(view);

	m_bgtilemap.setPosition({ player_pos.x - halfViewWidth, 0 });
}

void LevelWithTiles::render()
{
	beginDraw();
	m_bgtilemap.render(m_window);
	m_tilemap.render(m_window);
	m_window.draw(m_lever);
	for (auto& flag : m_flags) m_window.draw(*flag);
	for (auto& enemies : m_enemy) m_window.draw(*enemies);
	m_window.draw(m_player);
	for (auto& Projectile : m_player.getFired())
		m_window.draw(*Projectile);
	m_window.draw(m_alertText);
	if (m_pauseScene.getPauseState() == true) {
		sf::View world_view = m_window.getView();
		sf::Vector2f midScreen = world_view.getCenter();
		m_window.setView(m_window.getDefaultView());
		//m_pauseScene.setPosition(midScreen);
		m_pauseScene.render();
	}

	
	endDraw();
}

void LevelWithTiles::onBegin()
{
	m_gameState.setCurrentState(State::LEVELONE);
	if (m_gameState.getPreviousState() == State::MENU) {
		m_player.reset();
		m_flagLeverPulled = false;
		m_enemy.clear();
		m_enemy.push_back(Enemy::newEnemy(1, "gfx/EyeEnimy.png", 2.f, Tag::Player, 10.f, 64.f, 64.f, 0.f, 0.f, { 800,109 }, &m_player, 10));

		// reset alert text
		m_alertText.setString("Who keeps turning\nthe wind off?");
		m_alertText.setPosition({ 50, 150 });
		m_alertText.setCharacterSize(36);
		m_alertText.setFillColor(sf::Color::Black);
		m_promptTimer = PROMPT_TIME;
		// sfx
		m_audio.stopAllSounds();
		m_audio.stopAllMusic();
		
	}
		m_pauseScene.setPauseState(false);
		std::cout << "Level one has been started\n";
		m_audio.playMusicbyName("bgm1");
	

}

void LevelWithTiles::onEnd()
{
		m_gameState.setPreviousState(State::LEVELONE);
		std::cout << "Level one has been left\n";
		m_audio.stopAllSounds();
		m_audio.stopAllMusic();
}
