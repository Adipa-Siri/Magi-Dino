#pragma once
class Health
{
public:
	Health(int maxHP);
	~Health();
	int DamageTaken();
	bool isDead();
	//int getCurrentHP() { return m_currentHealth; };
protected:
	int m_maxHealth;
	int m_currentHealth;
	int m_damage;
	bool m_dead;

};

