#pragma once
class Health
{
public:
	Health(int maxHP);
	~Health();
	bool isDead();
	int getCurrentHP() { return m_currentHealth; };
protected:
	int m_maxHealth;
	int m_currentHealth;
	bool m_dead = false;

};

