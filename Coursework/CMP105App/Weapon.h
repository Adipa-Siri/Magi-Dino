#pragma once
#include "Health.h"
#include <iostream>
#include "Framework/GameObject.h"
class Weapon :public GameObject
{
public:
	Weapon(int maxHealth = 5);
	~Weapon();
	void update(float dt) override;
	void Cutter(int damage);
	/*void DarkMatter(int damage);*/
protected:
	GameObject m_cutter;
	sf::Texture m_cutterTexture;
	Health m_projectileLife;


	GameObject m_darkMatter;
	sf::CircleShape m_matter;
};

