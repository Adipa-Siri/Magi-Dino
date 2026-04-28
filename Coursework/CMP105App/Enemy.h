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
	static Enemy* newEnemy(int damage, const std::string file, float duration, Tag target, float speed, float width, float length, float x, float y, sf::Vector2f pos, Player* player, int health);
	void reset(sf::Vector2f pos);
	//void aggroRange(sf::Vector2f pos);


	void loadTexture(const std::string& filename);
	void setTextureName(std::string filename) { m_textureFile = filename; };
	std::string getTextureName() { return m_textureFile; };//for debugging
	void setDamage(int dam) { m_damageAmount = dam; m_damage.setHealth(dam); };
	int getDamage() { return m_damageAmount; };
	void setSpeed(float s) { m_speed = s; };
	float getSpeed() { return m_speed; };
	void Damage(int dam) { m_health.DamageTaken(dam); }
	void setDuration(float timer) { m_cooldownDuration = sf::seconds(timer); };
	sf::Time getDuration() { return m_cooldownDuration; };
	void setPlayer(Player* player) { m_playerRef = player; }
	//void setWaypoint(std::vector<sf::Vector2f>& WP);
	
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
	//sf::Time cooldown = sf::Time::Zero;
	sf::Time m_cooldown;
	sf::Time m_cooldownDuration;
	float m_speed;
	int m_damageAmount;
	Health m_damage;
	Tag m_tag;
	Player* m_playerRef;	// reference to player for enemy to track and move towards
	std::vector <sf::Vector2f*> m_waypoint;
	bool m_isFacingRight = false;

};

