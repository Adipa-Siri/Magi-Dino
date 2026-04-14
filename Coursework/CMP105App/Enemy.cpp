#include "Enemy.h"

Enemy::Enemy(int health, int dam):m_health(health), m_damage(dam), m_speed(50.f)
{
	m_tag = Tag::Enemy;
}

void Enemy::update(float dt)
{
	// Move towards the player
	sf::Vector2f direction = m_playerRef.getPosition() - getPosition();
	if (direction.lengthSquared() > 0) {
		direction = direction.normalized();
		move(direction * m_speed * dt);
	}
	m_health.update(dt);
	if (m_health.isDead())
		setAlive(false);
}

void Enemy::collisionResponse(GameObject& collider)
{
	// If we collide with the player, damage the player
	if (collider.isCollider() && collider.getTag() == Tag::Player) {
		Player& player = static_cast<Player&>(collider);
		player.getHealth().DamageTaken(m_damage);
	}
}
