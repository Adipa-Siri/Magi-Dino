#pragma once
#include<iostream>
class Health
{
public:
	Health(int maxHP);
	~Health();
	int DamageTaken(int dam);
	bool isDead();
	void setHealth(int maxHP);
	int getHealth() { return m_currentHealth; }
	void reset();
protected:
	int m_maxHealth;
	int m_currentHealth;
	bool m_dead;

};

