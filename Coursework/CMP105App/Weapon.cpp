#include "Weapon.h"
Weapon::Weapon(int maxHealth):m_projectileLife(maxHealth) {
	m_alive = false;
}

void Weapon::update(float dt) {
	while (m_alive == true && m_projectileLife.getHealth() > 0) {
		int dam = 1;
		m_projectileLife.DamageTaken(dam);

	}


}
void Weapon::Cutter(int m_damage = 2) {
	if (m_input->isLeftMousePressed()) {
		m_alive = true;
		
	}
	
}

Weapon::~Weapon() {}