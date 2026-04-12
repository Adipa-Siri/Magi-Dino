#include "Projectile.h"
Projectile::Projectile() :m_health(1), m_damage(m_damageAmount), m_direction(m_direction), m_speed(m_speed)
{
	m_tag = Tag::Projectile;
}

void Projectile::update(float dt)
{
	sf::Vector2f velocity(m_speed * m_direction.x*dt, m_speed * m_direction.y*dt);
	// Move the projectile according to its velocity
	move(velocity);
	// Update health (for projectiles that can be damaged or have a lifespan)
	m_health.update(dt);
	if (m_health.isDead())
		setAlive(false);
}

void Projectile::loadTexture(const std::string& filename)
{
	if (!m_bulletTexture.loadFromFile(filename))
		std::cerr << "No bullet texture. sad";
	setTexture(&m_bulletTexture);
	setTextureRect(sf::IntRect({ 0,0 }, { 64,64 }));
	setSize({ 64,64 });
	setCollisionBox({ {0,0}, getSize() });
}

Projectile* Projectile::newBullet(int damage, const std::string file, Tag target, float speed, sf::Vector2f& m_direction)
{
	Projectile* bullet = new Projectile();
	std::cout << "file received: " << file << "\n";
	bullet->setTextureName(file);
	bullet->loadTexture(file);
	bullet->setDamage(damage);
	bullet->setTargetTag(target);
	bullet->setSpeed(speed);

	return bullet;
}
Projectile::~Projectile()
{
}
