#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/Animation.h"
#include "Framework/Tag.h"
#include "Player.h"
#include <iostream>
class Enemy :public GameObject
{
public:
	Enemy(int health, int dam);
	~Enemy();
	void handleInput(float dt) override;
	void update(float dt) override;
	void collisionResponse(GameObject& collider) override;
	//static Enemy* newEnemy(int health, int dam) { return new Enemy(health, dam); };

private:
	GameObject m_enemyObject;
	sf::CircleShape m_sightbox;
	sf::Texture m_enemyTexture;
		Health m_health;
		Animation* m_currentAnim;
		Animation m_walk;
		Animation m_attack;
		Animation m_idle;
		float m_speed;
		int m_damage;
		Tag m_tag;
		Player m_playerRef;	// reference to player for enemy to track and move towards

};

