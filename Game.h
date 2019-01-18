// Michael Bridgette and Liam Hickey
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Player.h"
#include "Block.h"
#include "Level.h"
#include "MainMenu.h"
#include "endLevel.h"
#include "Bomb.h"
#include "Options.h"
#include "Hud.h"
#include "PauseMenu.h"
#include "ResourceManager.h"
#include"CreditsScreen.h"
#include"GameComplete.h"
#include"FadeScreen.h"
#include"DieScreen.h"
#include "XBOX360CONTROLLER.h"
#include "Splash.h"
// Test ---
#include "Enemy.h"
#include "Ghost.h"
// Test ---

class Level;
class Menu;
class EndLevelScreen;
class Options;
class Pause;
class CreditsScreen;
class GameCompleteScreen;
class FadeScreen;
class DieScreen;
class Splash;

enum GameState {
	MainMenu,
	Play,
	EndLevel,
	OptionsMenu,
	PauseScreen,
	Credits,
	Transition,
	EndGame,
	Die,
	TheSplash
};

class Game
{
public:
	// Public Functions
	Game();
	~Game();
	void run();
	void setGameState(GameState gameState);
	void loadLevel(std::string levelName);
	void endGame();
	void setMusicVolume(float volume);
	void setSfxVolume(float volume);
	void increaseLevel();
	sf::Shader & getShader();

	void toggleShader();
private:
	// Private functions
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	// Private members
	sf::RenderWindow m_window; // Main SFML window
	bool m_exitGame; // Control exiting game

	// Box2D members
	b2Vec2 Gravity;
	b2World World;
	Player* player;
	std::vector<Block*> blocks;

	Level *m_level;
	GameState m_gameState;
	Menu * m_menu;
	Options * m_options;
	EndLevelScreen * m_endLevelScreen;
	Pause * m_pauseScreen;
	CreditsScreen * m_credits;
	GameCompleteScreen * m_gameComplete;
	FadeScreen * m_fade;
	DieScreen * m_die;
	Splash * m_splash;

	sf::SoundBuffer m_musicBuffer;
	sf::Music m_music;
	sf::Texture blankShaderTexture;
	sf::Sprite blankShaderSprite;

	sf::Shader m_shader;
	float counter;
	HUD m_hud;

	int m_currentLevel = 1;
	int m_totalLevels = 3;

	Xbox360Controller m_xbox;

	bool shaderOn;
};

#endif //!Game