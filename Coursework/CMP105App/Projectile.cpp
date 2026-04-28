#include "Projectile.h"
Projectile::Projectile() :m_health(1), m_damage(m_damageAmount), m_direction(m_direction), m_speed(m_speed)
{

}

void Projectile::update(float dt)
{
	sf::Time timer = sf::seconds(dt);
	sf::Vector2f velocity(m_speed * m_direction.x*dt, m_speed * m_direction.y*dt);
	// Move the projectile according to its velocity
	move(velocity);
	// Update health (for projectiles that can be damaged or have a lifespan)
	m_health.update(dt);
	m_duration -= timer;
	if (m_duration <= sf::Time::Zero) {
		m_alive = false;
	}
}

void Projectile::collisionResponse(GameObject& collider)
{
	if (Collision::checkBoundingBox(*this, collider)) {

		collider.Damage(getDamage());
		m_alive = false;

	}
	
}

void Projectile::flipTexture()
{
	sf::IntRect rect = getTextureRect();
	rect.position.x += rect.size.x; // Move the left edge to the right edge
	rect.size.x = -rect.size.x; // Flip the width to negative to mirror the texture
	setTextureRect(rect);
}

//bullet factory
Projectile* Projectile::newBullet(int damage, const std::string file, float speed, sf::Vector2f& m_direction, float duration)
{
	Projectile* bullet = new Projectile();
	bullet->loadTexture(file,64,64,0.f,0.f);
	bullet->setDamage(damage);
	bullet->setDuration(duration);
	bullet->setSpeed(speed);
	return bullet;
}
Projectile::~Projectile()
{
}
