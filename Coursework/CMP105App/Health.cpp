#include "Health.h"

Health::Health(int maxHP):m_maxHealth(maxHP),m_currentHealth(maxHP),m_dead(false) {


}

int Health::DamageTaken(int dam) {

	m_currentHealth = m_currentHealth - dam;

	return m_currentHealth;

}

bool Health::isDead() {

	if (m_currentHealth <= 0) {
	m_dead = true;
}
	return m_dead;
}
Health::~Health() {}
