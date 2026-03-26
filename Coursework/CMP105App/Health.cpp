#include "Health.h"

Health::Health(int maxHP):m_maxHealth(maxHP),m_currentHealth(maxHP),m_dead(false) {
}

int Health::DamageTaken() {

	m_currentHealth = m_currentHealth - m_damage;

	return m_currentHealth;

}

bool Health::isDead() {
	return
	m_dead = true;
}
Health::~Health() {}
