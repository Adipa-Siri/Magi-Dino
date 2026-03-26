#pragma once
#include "Health.h"
#include <iostream>
#include "Framework/GameObject.h"
class Weapon :public GameObject, public Health
{
public:
	Weapon();
	~Weapon();
	void update(float dt) override;
	void Cutter(int damage);
	void DarkMatter(int damage);
protected:
	GameObject m_cutter;
	sf::Texture m_cutterTexture;


	GameObject m_darkMatter;
	sf::CircleShape m_matter;
};

