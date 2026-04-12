#pragma once
#include "Framework/GameObject.h"
#include "Health.h"
#include "Tag.h"
class Projectile: public GameObject
{
public:
	Projectile();
	~Projectile();
	void update(float dt);
	void loadTexture(const std::string& filename);
	void setTextureName(std::string filename) { m_textureFile = filename; };
	std::string getTextureName() { return m_textureFile; };//for debugging

	void setDamage(int dam) { m_damageAmount = dam; m_damage.setHealth(dam); };
	int getDamage() { return m_damageAmount; };

	void setTargetTag(Tag t) { m_targetTag = t; };

	void setSpeed(float s) { m_speed = s; };
	float getSpeed() { return m_speed; };

	void setDirection(sf::Vector2f& dir) { m_direction = dir; };
	sf::Vector2f& getDirection() { return m_direction; };

	static Projectile* newBullet(int damage, const std::string file, Tag target, float speed, sf::Vector2f& m_direction);

	

protected:
	bool m_flipped;
	std::string m_textureFile;
	sf::Texture m_bulletTexture;
	Health m_health;
	Health m_damage;
	int m_damageAmount;
	float m_speed;
	sf::Vector2f m_direction;
	Tag m_tag;
	Tag m_targetTag;	// The tag of the type of object this projectile can damage (e.g. Player, Enemy)
};

