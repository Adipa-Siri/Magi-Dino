#include "Pause.h"

Pause::Pause(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audioManager) :
	 m_gameState(gameState), m_pauseText(m_font), m_menuText(m_font), m_continueText(m_font), Scene(window, input, gameState, audioManager)
{
	sf::View world_view = window.getView();
	sf::Vector2f midScreen = world_view.getCenter();
	window.setView(window.getDefaultView());

	m_background = sf::RectangleShape({ window.getView().getSize() });
	m_background.setFillColor(sf::Color::Black);
	

	if (!m_font.openFromFile("font/bitcount.ttf"))
		std::cerr << "failed to load bitcount font";
	m_pauseText.setFont(m_font);
	m_menuText.setFont(m_font);
	m_continueText.setFont(m_font);
	m_pauseText.setCharacterSize(60);
	m_menuText.setCharacterSize(40);
	m_continueText.setCharacterSize(40);
	m_pauseText.setPosition({midScreen.x - 100, midScreen.y - 150});
	m_pauseText.setString("PAUSED");
	m_pauseText.setFillColor(sf::Color::White);
	m_pauseText.setFillColor(sf::Color::White);
	m_menuText.setFillColor(sf::Color::White);

	m_menuButton.setSize({ 200,50 });
	m_menuButton.setPosition({ midScreen.x - 100,200 });
	m_menuText.setPosition({ midScreen.x - 50,200 });
	m_menuText.setString("Menu");
	m_menuButton.setFillColor(sf::Color(100, 250, 100, 50));
	m_menuButton.setCollisionBox({ {0,0}, m_menuButton.getSize() });

	m_continueButton.setSize({ 200,50 });
	m_continueButton.setPosition({ midScreen.x - 100,350 });
	m_continueText.setPosition({ midScreen.x - 90,350 });
	m_continueText.setString("Continue");
	m_continueButton.setFillColor(sf::Color::Magenta);
	m_continueButton.setCollisionBox({ {0,0}, m_continueButton.getSize() });

	
}
//button click returning to game/menu
void Pause::handleInput(float dt)
{
	
	sf::Vector2i mousePos{ m_input.getMouseX(), m_input.getMouseY() };

	if (m_input.isLeftMousePressed())
	{
		std::cout << mousePos.x << mousePos.y << "\n";


	}
	if (m_input.isLeftMousePressed() && Collision::checkBoundingBox(m_menuButton, mousePos))
	{
		std::cout << "Menu button clicked\n";
		m_gameState.setCurrentState(State::MENU);
	}
	if (m_input.isLeftMousePressed() && Collision::checkBoundingBox(m_continueButton, mousePos))
	{
		std::cout << "unpause button clicked\n";
		unpause();
	}

	if(m_input.isPressed(sf::Keyboard::Scancode::Escape))
	{
		setPauseState(true);
		m_gameState.setPreviousState(State::PAUSE);
	}
}

void Pause::update(float dt)
{
	
}

void Pause::render()
{
	m_window.draw(m_background);
	m_window.draw(m_pauseText);
	m_window.draw(m_menuButton);
	m_window.draw(m_menuText);
	m_window.draw(m_continueButton);
	m_window.draw(m_continueText);
	
}

void Pause::unpause() {
	m_gameState.setCurrentState(m_gameState.getPreviousState());
}

void Pause::onBegin()
{
	auto view = m_window.getView();
	view.setCenter({ (m_window.getSize().x / 2.f), (m_window.getSize().y / 2.f) });
	m_window.setView(view);
	m_gameState.setCurrentState(State::PAUSE);
}

void Pause::onEnd()
{
	auto view = m_window.getView();
	view.setCenter({ (m_window.getSize().x / 2.f), (m_window.getSize().y / 2.f) });
	m_window.setView(view);
	m_gameState.setPreviousState(State::PAUSE);
}