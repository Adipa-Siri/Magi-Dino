#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/AudioManager.h"
#include "Player.h"
#include "Framework/TileMap.h"
#include "Framework/GameState.h"
#include "Scene.h"
class Pause : public Scene
{
public:
	Pause(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audioManager);

	void handleInput(float dt)override;
	void update(float dt) override;
	void render()override;
	bool getPauseState() { return m_isPaused; };
	void setPauseState(bool pause) { m_isPaused = pause; };
	void unpause();
	void onBegin()override;
	void onEnd() override;
private:
	sf::Text m_pauseText;
	sf::Text m_menuText;
	sf::Text m_continueText;
	sf::Font m_font;
	GameObject m_menuButton;
	GameObject m_continueButton;
	sf::RectangleShape m_background;
	bool m_isPaused;
	Player m_player;
	AudioManager m_audio;

	GameState& m_gameState;
};

