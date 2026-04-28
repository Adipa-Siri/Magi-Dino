#include "Enemy.h"

Enemy::Enemy():m_health(m_health), m_damage(m_damageAmount), m_speed(m_speed)
{
}

void Enemy::update(float dt)
{
	// Move towards the player
	sf::Vector2f direction = m_playerRef->getPosition() - getPosition();
	sf::Time timer = sf::seconds(dt);
	if (direction.lengthSquared() > 0) {
		direction = direction.normalized();
	}

	//for flipping sprite
	sf::Vector2f velocity = direction.normalized() * m_speed * dt;
	if (velocity.x * -1.f < 0 && !m_isFacingRight) {
		m_isFacingRight = true;
		flip();
	}
	if (velocity.x * -1.f >= 0 && m_isFacingRight) {

		m_isFacingRight = false;
		flip();

	}


	move(velocity);
	
	if (m_cooldown > sf::Time::Zero) {
		m_cooldown -= timer;
		
	}
	if (m_health.getHealth() <= 0) {
		setAlive(false);
	}
}

void Enemy::collisionResponse(GameObject& collider)
{
	// If we collide with the player, damage the player
	if (Collision::checkBoundingBox(*this, collider)) {
		if (m_cooldown <= sf::Time::Zero)
		{
		collider.Damage(getDamage());
		m_cooldown = getDuration();
		}
		
	}
}


void Enemy::reset(sf::Vector2f pos) {
	setAlive(true);
	setPosition(pos);
}


//flipping sprite to the opposite side everytime it's called
void Enemy::flip() {
	sf::IntRect rect = getTextureRect();
	rect.position.x += rect.size.x; 
	rect.size.x = -rect.size.x;
	setTextureRect(rect);

}

void Enemy::handleInput(float dt) {

}
//enemy factory
Enemy* Enemy::newEnemy(int damage, const std::string file, float duration, float speed, float width, float length, float x, float y, sf::Vector2f pos, Player* player, int health)
{
	Enemy* enemy = new Enemy();
	enemy->GameObject::loadTexture(file,width, length, x, y);
	enemy->m_health.setHealth(health);
	enemy->setSpeed(speed);
	enemy->setDamage(damage);
	enemy->setDuration(duration);
	enemy->setAlive(true);
	enemy->setPosition(pos);
	enemy->setPlayer(player);
	return enemy;
}

Enemy::~Enemy() {}