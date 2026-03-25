#include "Health.h"

Health::Health(int maxHP):m_maxHealth(maxHP),m_currentHealth(maxHP),m_dead(false) {
}

bool Health::isDead() {
	return
	m_dead = true;
}
Health::~Health() {}
