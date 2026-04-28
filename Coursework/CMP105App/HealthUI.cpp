#include "HealthUI.h"
HealthUI::HealthUI(): m_healthText(m_healthFont)
{
	if (!m_healthFont.openFromFile("font/bitcount.ttf"))
		std::cerr << "failed to load bitcount font";
	m_healthText.setFont(m_healthFont);




}
void HealthUI::render(sf::RenderWindow& win) {




}