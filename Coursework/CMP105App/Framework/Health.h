#pragma once
#include<iostream>
class Health 
{
public:
	Health(int maxHP);
	~Health();
	int DamageTaken(int dam);
	void setHealth(int maxHP);
	int getHealth() { return m_currentHealth; }
	void reset();
	void update(float dt);

	void setIsDead(bool dead) { m_dead = dead; };
	bool isDead() { return m_dead; };
protected:
	int m_maxHealth;
	int m_currentHealth;
	bool m_dead = false;

};

