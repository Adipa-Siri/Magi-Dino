#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/AudioManager.h"
#include "Player.h"
#include "Framework/TileMap.h"
#include "Framework/GameState.h"
class Pause : public GameObject
{
public:
	Pause(sf::RenderWindow& window, Input& input, GameState& gameState);

	void handleInput(float dt , Input& input);
	void update(float dt) override;
	void render(sf::RenderWindow* window);
	Pause* newPauseScene();
	bool getPauseState() { return m_isPaused; };
	//void onBegin();

private:
	sf::Text m_pauseText;
	sf::Font m_font;
	GameObject m_menuButton;
	sf::RectangleShape m_background;
	bool m_isPaused;


	GameState& m_gameState;
};

