#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
#include "Framework/AudioManager.h"
#include "Framework/Collision.h"
#include "Projectile.h"



class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void Damage(int dam) override;
    void collisionResponse(GameObject& collider) override;
    bool inLeverRange();
    bool inEndRange();
    void setLeverPulled(bool pulled) { m_leverPulled = pulled; };
    void respawn();
    void reset();
    void attack();
    //setter/getter
    bool canDoubleJump() { return m_canDoubleJump; };
    bool getLeverPulled() { return m_leverPulled; };
    bool getGameEndTriggered() { return m_gameEndTriggered; };
    void setEdges(float left, float right) { m_leftEdge = left; m_rightEdge = right; };
    void setLeverPosition(sf::Vector2f leverPos) { m_leverPosition = leverPos; };
    void setEndGamePosition(sf::Vector2f endPos) { m_endPosition = endPos; };
    void setCanDoubleJump(bool value) { m_canDoubleJump = value; };
    void setAudio(AudioManager* audio) { m_audio = audio; };
    bool getDeath() { return m_health.isDead(); };
    int getHealth() { return m_health.getHealth(); };
    
    std::vector<Projectile*>& getFired() { return m_bullets; };

private:
    std::vector<Projectile*> m_bullets;
    sf::Vector2f m_direction;
    sf::Texture m_dinoTexture;
    Animation* m_currAnim;
    Animation m_idle;
    Animation m_walk;
    Animation m_sprint;
    sf::Vector2f m_accel;
    float m_sprintTimer = 0.f;
    bool m_isGrounded;
    bool m_isFacingRight;
    float m_leftEdge;
    float m_rightEdge;
    sf::Vector2f m_leverPosition;
    sf::Vector2f m_endPosition;
    bool m_leverPulled = false;
    bool m_gameEndTriggered = false;
    bool m_canDoubleJump;
    bool m_hasDoubleJumped;
    AudioManager* m_audio;
    Health m_health;
    int m_maxHealth = 20;
    float m_cd;
   
    const float ATTACK_COOLDOWN = 2.f;
    const float SPRINT_COOLDOWN = 2.0f;
    const float SPRINT_SPEED_MULT = 2.5f;
    const float SPEED = 10.0f;
    const float GRAVITY = 50.0f;
    const float COEFF_OF_REST = 0.8f;
    const float DRAG_FACTOR = 0.9f;
    const float AIR_DRAG_FACTOR = 0.99f;
    const float TURN_DRAG = 0.6f;       // allow snappy decel for turning
    const float JUMP_FORCE = 15.0f;
    const float SPRINT_ANIM_THRESHOLD = 1.2f * SPEED;
    const float ACTIVATE_RANGE_SQUARED = 700.0f;
    

    

};

