#ifndef LEVEL_H
#define LEVEL_H

#include <string> // STD
#include <fstream> // STD
#include <iostream> // STD
#include <sstream> // STD
#include <map> // STD
#include <SFML\Graphics.hpp> // SFML
#include <SFML\Graphics\Shader.hpp> // SFML

#include "Block.h"
#include "Player.h"
#include "Goal.h"
#include "Game.h"
#include "MoveableBlock.h"
#include "Pickup.h"
#include "Enemy.h"
#include "Ghost.h"
#include "ResourceManager.h"

/// <summary>
/// Simple struuct to store the information about each different block type
/// </summary>
struct BlockID
{
	int x;
	int y;
	std::string id;
	bool destructible;
};

// Pre decalration for the game class as it is used within the level
class Game;

/// <summary>
/// Level class stores information about the level, i.e. the blocks, pickups and enemies etc.
/// </summary>
class Level
{
public:
	Level(int screenWidth, int screenHeight, Player &player, double t, Game& game, HUD * hudIn); // Contsructor
	~Level(); // Destructor
	void load(int level, b2World & world, int scale);
	void update(sf::RenderWindow & window, float windowMovementX, sf::Time t_deltaTime);
	void render(sf::RenderWindow & window);
	void setSoundVolume(float volume); // Allows the sound to be set from the options menu *********************************************
	
private:
	std::vector<sf::Text> m_helpMessages;
	sf::Font m_font;
	std::vector<Block*> m_blocks; // Vector for all the blocks in a level
	std::vector<MoveableBlock*> m_moveBlocks; // Vector for all the levels moveable blocks
	std::vector<Pickup*> m_pickups; // Vector for all thepickups in a level
	std::vector<Enemy*> m_enemies; // Vector for all the walking enemies in a level
	std::vector<Ghost*> m_ghosts; // Vector for all theghosts in a level
	Goal* m_goal; // The goal position
	sf::Texture m_backgroundTexture; // The texture used for the background
	sf::Sprite m_backgroundSprite1; // We have two backgrond sprites to allow for a scrolling world
	sf::Sprite m_backgroundSprite2;
	int m_screenWidth; // Screen dimensions
	int m_screenHeight;
	Player & player; // Player reference
	sf::Shader m_shader; // Shader will change between levels so the level needs to know about it
	Game * m_game;
	float timer;
	
	std::map<std::string, BlockID> m_blockMap; // Block map is used to store the BlockID structs in a map based on their ID's

	HUD * m_hud; // The level will update the HUD so we need access to it
};

#endif // !LEVEL_H