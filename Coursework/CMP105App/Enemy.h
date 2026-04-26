#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/Animation.h"
#include "Framework/Tag.h"
#include "Player.h"
#include "Projectile.h"
#include <iostream>
class Enemy :public GameObject
{
public:
	Enemy();
	~Enemy();
	void handleInput(float dt) override;
	void update(float dt) override;
	void collisionResponse(GameObject& collider) override;
	void flip();
	static Enemy* newEnemy(int damage, const std::string file, Tag target, float speed, float width, float length, float x, float y, sf::Vector2f& m_direction, float duration);


	void loadTexture(const std::string& filename);
	void setTextureName(std::string filename) { m_textureFile = filename; };
	std::string getTextureName() { return m_textureFile; };//for debugging
	void setDamage(int dam) { m_damageAmount = dam; m_damage.setHealth(dam); };
	int getDamage() { return m_damageAmount; };
	void setSpeed(float s) { m_speed = s; };
	float getSpeed() { return m_speed; };

private:
	GameObject m_enemyObject;
	sf::Texture m_enemyTexture;
	std::string  m_textureFile;
	Projectile m_bullet;
	Health m_health;
	/*Animation* m_currentAnim;
	Animation m_walk;
	Animation m_attack;
	Animation m_idle;*/


	float m_speed;
	int m_damageAmount;
	Health m_damage;
	Tag m_tag;
	Player m_playerRef;	// reference to player for enemy to track and move towards
	bool m_isFacingRight = false;

};

