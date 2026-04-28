#include "LevelTwoWithTiles.h"

LevelTwoWithTiles::LevelTwoWithTiles(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio)
	: Scene(window, input, gameState, audio), m_alertText(m_font), m_pauseScene(window, input, gameState,audio)
{
	//functin
	loadTile();
	loadBG();
	
	// setup player 
	m_player.setInput(&m_input);
	m_player.setEdges(0, WORLD_SIZE.x);
	m_player.setPosition({ 100, 100 });
	m_player.setAudio(&m_audio);

	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";

	// other bits
	sf::Vector2f boop_location = { 100, 72 * 2 + 100 };

	if (!m_tileTexture.loadFromFile("gfx/tilemap.png")) std::cerr << "failed to find tile images";
	m_coin.setTexture(&m_tileTexture);
	m_coin.setPosition(boop_location);
	m_coin.setSize({ 72,72 });
	m_coin.setAlive(false);
	m_coin.setCollisionBox({ { 0,0 }, { 72,72 } });

	m_boopBlock.setTexture(&m_tileTexture);
	m_boopBlock.setTextureRect({ {10 * 19,0}, { 18,18 } });
	m_boopBlock.setAlive(false);
	m_boopBlock.setCollisionBox({ { 0,0 }, { 72,72 } });
	m_boopBlock.setPosition(boop_location);
	m_boopBlock.setSize({ 72, 72 });

	m_flag.setPosition({ 38 * 72, 5 * 72 });
	m_flag.setSize({ 72,72 });
	m_flag.setTexture(&m_tileTexture);

	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";
	m_alertText.setPosition({ 50, 150 });
	m_alertText.setCharacterSize(36);
	m_alertText.setFillColor(sf::Color::Black);

	

}
//load ground tiles for lv2
void LevelTwoWithTiles::loadTile() {

	GameObject tile;
	std::vector<GameObject> tileset;
	std::ifstream tileSets("data/groundTile2.txt");
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
	m_tilemap.setPosition({ 0, 0 });
	m_tilemap.buildLevel();

	tileset.clear();
}

void LevelTwoWithTiles::loadBG() {
	GameObject tile;
	std::vector<GameObject> tileset;
	std::ifstream tileSets("data/BG2.txt");
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
	sf::Vector2u mapDimensions = { 14,5 };

	while (tileSets >> tileData) {
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
	m_bgtilemap.setPosition({ 0, -200 });
	m_bgtilemap.buildLevel();

	// setup player 
	m_player.setInput(&m_input);
	m_player.setEdges(0, WORLD_SIZE.x);
	m_player.setPosition({ 100, 100 });
	m_player.setAudio(&m_audio);

	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";

	// other bits
	sf::Vector2f boop_location = { 100, 72 * 2 + 100 };

	if (!m_tileTexture.loadFromFile("gfx/tilemap.png")) std::cerr << "failed to find tile images";
	m_coin.setTexture(&m_tileTexture);
	m_coin.setPosition(boop_location);
	m_coin.setSize({ 72,72 });
	m_coin.setAlive(false);
	m_coin.setCollisionBox({ { 0,0 }, { 72,72 } });

	m_boopBlock.setTexture(&m_tileTexture);
	m_boopBlock.setTextureRect({ {10 * 19,0}, { 18,18 } });
	m_boopBlock.setAlive(false);
	m_boopBlock.setCollisionBox({ { 0,0 }, { 72,72 } });
	m_boopBlock.setPosition(boop_location);
	m_boopBlock.setSize({ 72, 72 });

	m_flag.setPosition({ 38 * 72, 5 * 72 });
	m_flag.setSize({ 72,72 });
	m_flag.setTexture(&m_tileTexture);

	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";
	m_alertText.setPosition({ 50, 150 });
	m_alertText.setCharacterSize(36);
	m_alertText.setFillColor(sf::Color::Black);

	

}

void LevelTwoWithTiles::onBegin()
{
	m_gameState.setCurrentState(State::LEVELTWO);

	if (m_gameState.getPreviousState() == State::MENU||m_gameState.getPreviousState()==State::LEVELONE) {
		m_player.reset();
		m_enemy.clear();
		m_enemy.push_back(Enemy::newEnemy(4, "gfx/EyeEnimy.png", 1.f, 100.f, 64.f, 64.f, 0.f, 0.f, { 200,109 }, &m_player, 30));
		m_enemy.push_back(Enemy::newEnemy(1, "gfx/EyeEnimy.png", 1.f, 200.f, 64.f, 64.f, 0.f, 0.f, { 700,60 }, &m_player, 60));
		m_player.setCanDoubleJump(false);
		m_pointcount = 0;
		// sfx
		m_boopBlock.setAlive(false);
		m_coin.setAlive(false);
		m_player.setPosition({ 100, 100 });
		m_audio.stopAllSounds();
		m_audio.stopAllMusic();

	}
	m_audio.playMusicbyName("bgm3");
	m_pauseScene.setPauseState(false);
}

void LevelTwoWithTiles::onEnd()
{
	m_audio.stopAllSounds();
	m_audio.stopAllMusic();
	m_gameState.setPreviousState(State::LEVELTWO);
}

void LevelTwoWithTiles::handleInput(float dt)
{
	if (m_pauseScene.getPauseState() == false)
	{
		m_player.handleInput(dt);

		if (m_input.isPressed(sf::Keyboard::Scancode::M))
			m_gameState.setCurrentState(State::MENU);
	}

	if (m_input.isPressed(sf::Keyboard::Scancode::Escape)) {
		m_gameState.setCurrentState(State::PAUSE);
		m_pauseScene.handleInput(dt);
	}

	// if I press F on the flag  / I press escape.
	if (((m_flag.getPosition() - m_player.getPosition()).length() < 75 && m_pointcount > 0 &&
		m_input.isPressed(sf::Keyboard::Scancode::F)) ||
		m_input.isPressed(sf::Keyboard::Scancode::Escape))
	{
		// return to menu.
		m_gameState.setCurrentState(State::MENU);
	}
}

void LevelTwoWithTiles::update(float dt)
{
	auto& bullet = m_player.getFired();
	auto& enemies = m_enemy;

	if (m_pauseScene.getPauseState() == true)
	{
		return;
	}
	for (auto eye = enemies.begin(); eye != enemies.end();) {

		(*eye)->collisionResponse(m_player);
		(*eye)->update(dt);

		if ((*eye)->isAlive() == false) {
			delete (*eye);
			eye = enemies.erase(eye);
			++m_pointcount;
		}
		else ++eye;

	}

	for (auto projectile = bullet.begin(); projectile != bullet.end();) {
		(*projectile)->update(dt);
		for (auto& eye : m_enemy)
			(*projectile)->collisionResponse(*eye);


		if (!(*projectile)->isAlive()) {
			delete (*projectile);
			projectile = bullet.erase(projectile);

		}
		else ++projectile;

	}



	m_player.update(dt);
	m_flag.update(dt);
	if (m_coin.isAlive()) m_coin.update(dt);

	// handle collisions
	std::vector<GameObject>& level = *m_tilemap.getLevel();
	for (auto& t : level)
	{
		if (t.isCollider() && Collision::checkBoundingBox(m_player, t))
		{
			m_player.collisionResponse(t);
		}	
	}

	if (m_boopBlock.isAlive())
	{
		if (Collision::checkBoundingBox(m_player, m_boopBlock))
		{
			if (m_player.getPosition().y >= m_boopBlock.getPosition().y)
			{
				// if booped from below
				m_boopBlock.setAlive(false);
				m_coin.setAlive(true);
			}
			m_player.collisionResponse(m_boopBlock);

		}
	}

	if (m_coin.isAlive())
	{
		if (Collision::checkBoundingBox(m_player, m_coin))
		{
			m_coin.setAlive(false);
			m_player.setCanDoubleJump(true);
		}
	}

	// turn block on when at wall.
	if ((m_wallPos - m_player.getPosition()).length() < 75)
	{
		m_boopBlock.setAlive(true);
	}

	// reset if fallen too far
	if (m_player.getPosition().y > 1200 || m_player.getDeath() == true)
	{
		m_player.respawn();
		m_audio.playSoundbyName("death");
	}

	updateCameraAndBackground();
	checkAndSetMessages();
}

void LevelTwoWithTiles::updateCameraAndBackground()
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

// sets prompt text and position 
void LevelTwoWithTiles::checkAndSetMessages()
{
	// get position 25% in from top and left (get middle, half both dimensions)
	sf::Vector2f inner_top_left = m_window.getView().getCenter();
	sf::Vector2f window_size = { 
		static_cast<float>(m_window.getSize().x), 
		static_cast<float>(m_window.getSize().y) };
	inner_top_left -= window_size * 0.25f;
	// big wall 
	if (!m_player.canDoubleJump() && 
		(m_wallPos - m_player.getPosition()).length() < 75)
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(inner_top_left);
		m_alertText.setString(m_promptMessages[0]);
		
	}
	// double jump unlocked
	else if (m_player.canDoubleJump() && 
		(m_boopBlock.getPosition() - m_player.getPosition()).length() < 150)
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(inner_top_left);
		m_alertText.setString(m_promptMessages[1]);
	}

	// complete level
	else if ((m_flag.getPosition() - m_player.getPosition()).length() < 75)
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(inner_top_left);
		m_alertText.setString(m_promptMessages[2]);
	}
	else
	{
		m_alertText.setPosition({ 0,-100 });
	}
}

void LevelTwoWithTiles::HUD() {
	auto world_view = m_window.getView();
	sf::Vector2f midScreen = world_view.getCenter();
	sf::Vector2f v_size = world_view.getSize();
	m_window.setView(m_window.getDefaultView());
	float x = v_size.x / 3.f;
	float y = v_size.y / 5.f;
	m_UI.setPosition({ x,y });
	m_UI.update(m_player);
	m_UI.render(m_window);
	m_window.setView(world_view);

}

void LevelTwoWithTiles::render()
{
	beginDraw();
	m_bgtilemap.render(m_window);
	m_tilemap.render(m_window);
	if (m_boopBlock.isAlive()) m_window.draw(m_boopBlock);
	m_window.draw(m_flag);
	m_window.draw(m_player);
	if (m_coin.isAlive()) m_window.draw(m_coin);
	m_window.draw(m_alertText);
	for (auto& enemies : m_enemy) m_window.draw(*enemies);
	m_window.draw(m_player);
	for (auto& Projectile : m_player.getFired())
		m_window.draw(*Projectile);

	HUD();
	if (m_pauseScene.getPauseState() == true) {
		sf::View world_view = m_window.getView();
		sf::Vector2f midScreen = world_view.getCenter();
		m_window.setView(m_window.getDefaultView());
		//m_pauseScene.setPosition(midScreen);
		m_pauseScene.render();
	}
	endDraw();
}