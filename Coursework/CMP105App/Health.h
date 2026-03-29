#pragma once
#include<iostream>
#include "Component.h"
class Health :public Component
{
public:
	Health(int maxHP);
	~Health();
	int DamageTaken(int dam);
	bool isDead();
	void setHealth(int maxHP);
	int getHealth() { return m_currentHealth; }
	void reset();
	void update(Entities& obj, float dt) override;
protected:
	int m_maxHealth;
	int m_currentHealth;
	bool m_dead;

};

