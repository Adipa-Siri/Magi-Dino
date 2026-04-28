#pragma once
//#include "Health.h"
#include "Player.h"
#include "Framework/GameObject.h"
#include <iostream>
class HealthUI :public GameObject
{
public:
	HealthUI();
	void update(Player& player);
	~HealthUI() {};
	void render(sf::RenderWindow& win);
protected:
	sf::Text m_healthText;
	sf::Font m_healthFont;


};

