#include "Pause.h"

Pause::Pause(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio) :
	Scene(window, input, gameState, audio), m_gameState(gameState), m_pauseText(m_font)
{
	m_window.setMouseCursorVisible(true);
	m_window.getSize();
	m_background = sf::RectangleShape({ (float)m_window.getSize().x, (float)m_window.getSize().y });
	m_background.setFillColor(sf::Color(0, 0, 0, 150));

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

void Pause::handleInput(float dt)
{
	sf::Vector2i mousePos{ m_input.getMouseX(), m_input.getMouseY() };
	if (m_input.isLeftMousePressed() &&
		Collision::checkBoundingBox(m_menuButton, mousePos))
	{
		m_gameState.setCurrentState(State::MENU);
	}
}

void Pause::update(float dt)
{
}

void Pause::render(sf::RenderWindow* window)
{
	beginDraw();
	m_window.draw(m_background);
	m_window.draw(m_pauseText);
	m_window.draw(m_menuButton);
	endDraw();
}

void Pause::onBegin()
{
	auto view = m_window.getView();
	view.setCenter({ (m_window.getSize().x / 2.f), (m_window.getSize().y / 2.f) });
	m_window.setView(view);
}

void Pause::onEnd()
{
}