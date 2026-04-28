#pragma once
#include "Scene.h"
#include "Framework/Collision.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Coin.h"
#include "Flag.h"
#include "Pause.h"
#include "Enemy.h"
#include "Projectile.h"
#include "HealthUI.h"
#include <fstream>
#include <algorithm> // for clamp


class LevelTwoWithTiles :
    public Scene
{
public:
    LevelTwoWithTiles(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio);

    void handleInput(float dt) override;
    void update(float dt) override;
    void render() override;
    void onBegin() override;
    void onEnd() override;
    void loadTile();
    void loadBG();
    void HUD();
private:
    void updateCameraAndBackground();
    void checkAndSetMessages();
    int m_blank;
    TileMap m_tilemap;
    TileMap m_bgtilemap;
    Player m_player;
	
    std::vector<Enemy*> m_enemy;
    HealthUI m_UI;

    Coin m_coin;
    GameObject m_boopBlock;
    Flag m_flag;
    int m_pointcount = 0;
    const sf::Vector2i WORLD_SIZE = { 2880, 648 };
    const sf::Vector2i VIEW_SIZE = { 432, 432 };

    sf::Text m_alertText;
    sf::Font m_font;
    sf::Texture m_tileTexture;

    sf::Vector2f m_wallPos = { 11 * 72, 5 * 72 };

	Pause m_pauseScene;


    std::vector<std::string> m_promptMessages =
    {
        "Oh I'm stuck.\nMaybe I missed\nsomething back there?",
        "I feel so powerful\nalmost like I\ncan double-jump",
        "Press F to end the day"
    };
};

