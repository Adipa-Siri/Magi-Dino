#pragma once
class Health
{
public:
	Health(int maxHP);
	~Health();
	int DamageTaken(int dam);
	bool isDead();
	int getHealth() { return m_currentHealth; }
	//int getCurrentHP() { return m_currentHealth; };
protected:
	int m_maxHealth;
	int m_currentHealth;
	bool m_dead;

};

