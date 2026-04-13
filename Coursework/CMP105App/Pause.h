#pragma once
#include "Framework/Collision.h"
#include "Scene.h"
class Pause : public Scene
{
public:
	Pause(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio);

	void handleInput(float dt);
	void update(float dt);
	void render(sf::RenderWindow* window);
	void onBegin() override;
	void onEnd() override;

	bool setPaused(bool paused) { m_isPaused = paused; return m_isPaused; };

private:
	sf::Text m_pauseText;
	sf::Font m_font;
	GameObject m_menuButton;
	sf::RectangleShape m_background;
	sf::RenderWindow m_window;
	bool m_isPaused;


	GameState& m_gameState;
};

