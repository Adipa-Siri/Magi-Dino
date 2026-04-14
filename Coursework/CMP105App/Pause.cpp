#include "Pause.h"

Pause::Pause(sf::RenderWindow& window, Input& input, GameState& gameState) :
	 m_gameState(gameState), m_pauseText(m_font)
{
	sf::View world_view = window.getView();
	sf::Vector2f midScreen = world_view.getCenter();
	window.setView(window.getDefaultView());

	m_background = sf::RectangleShape({ window.getView().getSize() });
	m_background.setFillColor(sf::Color::Black);
	m_background.setPosition({ 0, 0 });

	if (!m_font.openFromFile("font/bitcount.ttf"))
		std::cerr << "failed to load bitcount font";
	m_pauseText.setFont(m_font);
	m_pauseText.setCharacterSize(48);
	m_pauseText.setPosition({ 150, 100 });
	m_pauseText.setString("PAUSED");
	m_pauseText.setFillColor(sf::Color::White);

	m_menuButton.setSize({ 200,50 });
	m_menuButton.setPosition({ 150,200 });
	m_menuButton.setFillColor(sf::Color(100, 250, 100, 50));
	m_menuButton.setCollisionBox({ {0,0}, m_menuButton.getSize() });

	
}

void Pause::handleInput(float dt, Input& input)
{
	sf::Vector2i mousePos{ input.getMouseX(), input.getMouseY() };
	if (input.isLeftMousePressed() && Collision::checkBoundingBox(m_menuButton, mousePos))
	{
		std::cout << "Menu button clicked\n";
		m_gameState.setCurrentState(State::MENU);
	}
	if(input.isPressed(sf::Keyboard::Scancode::P))
	{
		m_isPaused = !m_isPaused;
		if (m_isPaused == true)
		{
			//m_gameState.setCurrentState(State::PAUSE);
			std::cout << "Pause\n";
		}
	}
}

void Pause::update(float dt)
{
	
}

void Pause::render(sf::RenderWindow* window)
{
	window->draw(m_background);
	window->draw(m_pauseText);
	window->draw(m_menuButton);
	
}

Pause* Pause::newPauseScene()
{
	Pause* newScene = new Pause(*m_window, *m_input, m_gameState);
	return newScene;
}

//void Pause::onBegin()
//{
//	auto view = window.getView();
//	view.setCenter({ (window.getSize().x / 2.f), (window.getSize().y / 2.f) });
//	window.setView(view);
//}
//
//void Pause::onEnd()
//{
//	auto view = m_window.getView();
//	view.setCenter({ (m_window.getSize().x / 2.f), (m_window.getSize().y / 2.f) });
//	m_window.setView(view);
//}