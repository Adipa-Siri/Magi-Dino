#include "Health.h"

Health::Health(int maxHP):m_maxHealth(maxHP),m_currentHealth(maxHP),m_dead(false){
	

}

void Health::update(float dt) {
	if (m_currentHealth <= 0) {
		m_dead = true;
	}
}

int Health::DamageTaken(int dam) {
	m_currentHealth = m_currentHealth - dam;
	return m_currentHealth;

}
void Health::setHealth(int maxHP) {

	m_currentHealth = maxHP; 

}


void Health::reset() {
	m_currentHealth = m_maxHealth;
	m_dead = false;
	std::cout << m_currentHealth << "\n";
}
Health::~Health() {}
