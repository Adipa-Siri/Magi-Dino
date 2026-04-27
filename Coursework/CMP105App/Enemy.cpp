#include "Enemy.h"

Enemy::Enemy():m_health(m_health), m_damage(m_damageAmount), m_speed(m_speed)
{
setAlive(true);
setTag(Tag::Enemy);
}

void Enemy::update(float dt)
{
	// Move towards the player
	sf::Vector2f direction = m_playerRef->getPosition() - getPosition();
	if (direction.lengthSquared() > 0) {
		direction = direction.normalized();
	}
	sf::Vector2f velocity = direction.normalized() * m_speed * dt;
	std::cout << getPosition().x << " " << getPosition().y << "\n";
	if (velocity.x * -1.f < 0 && !m_isFacingRight) {
		m_isFacingRight = true;
		flip();
	}
	if (velocity.x * -1.f >= 0 && m_isFacingRight) {

		m_isFacingRight = false;
		flip();

	}
	move(velocity);

	if (m_health.getHealth() <= 0) {
		setAlive(false);
	}

}

void Enemy::collisionResponse(GameObject& collider)
{
	// If we collide with the player, damage the player
	if (Collision::checkBoundingBox(*this, collider)) {
		collider.Damage(m_damageAmount);
	}
}

void Enemy::reset(sf::Vector2f pos) {
	setAlive(true);
	setPosition(pos);



}

void Enemy::flip() {
	sf::IntRect rect = getTextureRect();
	rect.position.x += rect.size.x; 
	rect.size.x = -rect.size.x;
	setTextureRect(rect);

}

void Enemy::handleInput(float dt) {

}

Enemy* Enemy::newEnemy(int damage, const std::string file, Tag target, float speed, float width, float length, float x, float y, sf::Vector2f pos, Player* player)
{
	Enemy* enemy = new Enemy();
	enemy->GameObject::loadTexture(file,width, length, x, y);
	enemy->setSpeed(speed);
	enemy->setDamage(damage);
	enemy->setAlive(true);
	enemy->setPosition(pos);
	enemy->setPlayer(player);
	return enemy;
}

Enemy::~Enemy() {}