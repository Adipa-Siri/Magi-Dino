#pragma once
#include "Framework/GameObject.h"
#include"Framework/Collision.h"
class Projectile: public GameObject
{
public:
	Projectile();
	~Projectile();
	void update(float dt);
	void collisionResponse(GameObject& collider) override;

	//setter getter
	void setTextureName(std::string filename) { m_textureFile = filename; };
	void setDamage(int dam) { m_damageAmount = dam; m_damage.setHealth(dam); };
	int getDamage() { return m_damageAmount; };
	void setSpeed(float s) { m_speed = s; };
	float getSpeed() { return m_speed; };
	void setDirection(sf::Vector2f& dir) { m_direction = dir; };
	sf::Vector2f& getDirection() { return m_direction; };
	void setFlipped(bool flip) { m_flipped = flip; };
	bool getFlipped() { return m_flipped; };
	void flipTexture();
	bool getAlive() { return m_alive; };
	void setDuration(float timer) { m_duration = sf::seconds(timer); };
	sf::Time getDuration() { return m_duration; };

	static Projectile* newBullet(int damage, const std::string file, float speed, sf::Vector2f& m_direction, float duration);

protected:

	bool m_flipped;
	std::string m_textureFile;
	sf::Texture m_bulletTexture;
	Health m_health;
	Health m_damage;
	int m_damageAmount;
	float m_speed;
	sf::Vector2f m_direction;
	sf::Time m_duration;
};

