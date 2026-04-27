#pragma once
#include "Scene.h"
#include "Framework/Collision.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Lever.h"
#include "Flag.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Pause.h"
#include <algorithm>

class LevelWithTiles :
    public Scene
{
public:
    LevelWithTiles(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio);

    void handleInput(float dt) override;
    void update(float dt) override;
    void render() override;
    void onBegin() override;
    void onEnd() override;

private:
    void updateCameraAndBackground();

    TileMap m_tilemap;
    TileMap m_bgtilemap;
    Player m_player;
    sf::Texture m_tileTexture;
    Lever m_lever;
    sf::Text m_alertText;
    sf::Font m_font;
    
    std::vector<Flag*> m_flags;
    bool m_flagLeverPulled = false;
    float m_promptTimer;
	Pause m_pauseScene;

    std::vector<Enemy*> m_enemy;

    const float PROMPT_TIME = 2.f;
    const sf::Vector2i WORLD_SIZE = { 2880, 648 };
    const sf::Vector2i VIEW_SIZE = { 432, 432 };




};

