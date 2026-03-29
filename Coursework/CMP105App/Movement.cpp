#include "Movement.h"
Movement::Movement(float sp) : Component(), m_speed(sp), m_entity(m_entity) {
}
void Movement::Walk() {


}
void Movement::Jump() {


}
void Movement::update(Entities& obj, float dt) {
	m_entity.m_x += obj.m_velocityX * dt;
	m_entity.m_y += obj.m_velocityY * dt;
}
