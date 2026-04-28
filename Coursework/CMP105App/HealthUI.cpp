#include "HealthUI.h"
HealthUI::HealthUI(): m_healthText(m_healthFont)
{
	if (!m_healthFont.openFromFile("font/bitcount.ttf"))
		std::cerr << "failed to load bitcount font";
	m_healthText.setFont(m_healthFont);
	m_healthText.setCharacterSize(25);
	m_healthText.setFillColor(sf::Color::Black);
	m_healthText.setOutlineThickness(10);


}
void HealthUI::update(Player& player) {
		if (player.getHealth() > 14) m_healthText.setOutlineColor(sf::Color::Green);
		else if (player.getHealth() <= 14 && player.getHealth() > 5 )  m_healthText.setOutlineColor(sf::Color::Yellow);
		else m_healthText.setOutlineColor(sf::Color::Red);
	m_healthText.setString("HP:" + std::to_string(player.getHealth()));
}
void HealthUI::render(sf::RenderWindow& win) {
	win.draw(m_healthText);
}