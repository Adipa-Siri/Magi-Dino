#include "Enemy.h"

Enemy::Enemy(int health, int dam):m_health(health), m_damage(dam), m_speed(50.f)
{
	if (!m_enemyTexture.loadFromFile("gfx/pixilart-sprite(3).png"))
		std::cout << "Where my enimem\n";
	setTexture(& m_enemyTexture);
	setSize({ 576,576 });


setTag(Tag::Enemy);
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
		player.Damage(m_damage);
	}
}

void Enemy::handleInput(float dt) {

}

//Enemy* Enemy::newEnemy(int health, int dam)
//{
//	return new Enemy(health, dam);
//}

Enemy::~Enemy() {}