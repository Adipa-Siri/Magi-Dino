#include "Weapon.h"
Weapon::Weapon() :Health(m_damage){
	m_alive = false;
}


void Weapon::Cutter(int m_damage = 2) {
	if (m_input->isLeftMousePressed()) {
		m_alive = true;
	}
	while (m_alive == true) {
		if (!m_cutterTexture.loadFromFile("gfx/rotated cutter.png")) std::cerr << "Where is cutter?";
		m_cutter.setTexture(&m_cutterTexture);
	}





}

Weapon::~Weapon() {}