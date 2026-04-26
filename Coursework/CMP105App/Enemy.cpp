#include "Enemy.h"

Enemy::Enemy():m_health(m_health), m_damage(m_damageAmount), m_speed(m_speed)
{
setTag(Tag::Enemy);
}

void Enemy::update(float dt)
{
	// Move towards the player
	sf::Vector2f direction = m_playerRef.getPosition() - getPosition();

	if (direction.x * -1.f < 0) {
		flip();
	}

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
		player.Damage(m_damageAmount);
	}
}


void Enemy::flip() {
	sf::IntRect rect = getTextureRect();
	rect.position.x += rect.size.x; 
	rect.size.x = -rect.size.x;
	setTextureRect(rect);

}

void Enemy::handleInput(float dt) {

}

Enemy* Enemy::newEnemy(int damage, const std::string file, Tag target, float speed, float width, float length, float x, float y, sf::Vector2f& m_direction, float duration)
{
	Enemy* enemy = new Enemy();
	enemy->GameObject::loadTexture(file,width, length, x, y);
	enemy->setSpeed(speed);
	enemy->setDamage(damage);
	enemy->setAlive(true);

	return enemy;
}

Enemy::~Enemy() {}