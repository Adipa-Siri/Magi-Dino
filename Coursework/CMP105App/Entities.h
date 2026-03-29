#pragma once
#include "Component.h"
#include "Tag.h"
class Entities
{
public:
	float m_x, m_y;
	float m_velocityX, m_velocityY;

	Component* m_health;
	Component* m_weapon;
	Component* m_movement;
	Component* m_input;
	Component* m_sprite;
	Tag m_tag;
	Entities(Component* m_health, Component* m_weapon, Component* m_movement, Component* m_input, Component* m_sprite, Tag m_tag) {} 
	//:m_health(m_health), m_weapon(m_weapon), m_movement(m_movement), m_input(m_input), m_sprite(m_sprite) {}


};


