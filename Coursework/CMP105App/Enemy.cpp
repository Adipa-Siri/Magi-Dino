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

void Enemy::loadTexture(const std::string& filename) {




}

void Enemy::flip() {
	sf::IntRect rect = getTextureRect();
	rect.position.x += rect.size.x; 
	rect.size.x = -rect.size.x;
	setTextureRect(rect);

}

void Enemy::handleInput(float dt) {

}

//Enemy* Enemy::newEnemy(int health, int dam, std::string file, float speed, sf::Vector2f dir)
//{
//	Enemy* enemy = new Enemy();
//	enemy->loadTexture(file,64,64,0.f,0.f);
//
//	return enemy;
//}

Enemy::~Enemy() {}