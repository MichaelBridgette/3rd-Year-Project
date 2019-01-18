#include "Level.h"

/// <summary>
/// Level constructor mostly used to set up pointers and references
/// </summary>
/// <param name="screenWidth">The width of the screen</param>
/// <param name="screenHeight">The height of the screen</param>
/// <param name="player"A reference to the player</param>
/// <param name="t">The current time</param>
/// <param name="game">A reference to the game</param>
/// <param name="hudIn">A pointer to the HUD</param>
Level::Level(int screenWidth, int screenHeight, Player & player, double t, Game & game, HUD * hudIn)
	: m_screenWidth(screenWidth), 
	m_screenHeight(screenHeight), 
	player(player), timer(0), 
	m_game(&game), 
	m_hud(hudIn) 
{
	m_font.loadFromFile("Adventurer.ttf");
}

/// <summary>
/// Default Level Destructor
/// </summary>
Level::~Level() 
{
	for (auto & b : m_blocks)
	{
		delete b;
	}
	for (auto & b : m_moveBlocks)
	{
		delete b;
	}
	for (auto & b : m_pickups)
	{
		delete b;
	}
	for (auto & e : m_enemies)
	{
		delete e;
	}
	for (auto & g : m_ghosts)
	{
		delete g;
	}
	delete m_goal;
}

/// <summary>
/// Main load function for the level, sets up all aspects of a level
/// </summary>
/// <param name="level">The level number to be loaded</param>
/// <param name="world">A reference to the world</param>
/// <param name="scale">The scale fo the world</param>
void Level::load(int level, b2World & world, int scale)
{
	std::string prefix = "Level" + std::to_string(level);
	
	// Clear the level first
	for (auto & b : m_blocks)
	{
		delete b;
	}
	for (auto & b : m_moveBlocks)
	{
		delete b;
	}
	for (auto & b : m_pickups)
	{
		delete b;
	}
	for (auto & e : m_enemies)
	{
		delete e;
	}
	for (auto & g : m_ghosts)
	{
		delete g;
	}
	delete m_goal;
	m_helpMessages.clear();
	m_blocks.clear();
	m_moveBlocks.clear();
	m_pickups.clear();
	m_enemies.clear();
	m_ghosts.clear();
	player.playerReset(100, 100); // Reset the player position

	// Load all assets
	std::ifstream loader; // Loading done using a text file
	int x;
	int y;
	int xMin;
	int xMax;
	std::string id;
	bool destructible;

	loader.open(prefix + "\\blockid.txt"); // Load the block ID's
	while (loader >> x >> y >> id >> destructible)
	{
		BlockID bId;
		bId.x = x;
		bId.y = y;
		bId.id = id;
		bId.destructible = destructible;
		m_blockMap[id] = bId;
	}
	loader.close();
	loader.open(prefix + "\\goal.txt"); // Load the goal
	while (loader >> x >> y)
	{
		m_goal = new Goal("", x, y);
	}
	loader.close();
	loader.open(prefix + "\\moveable.txt"); // Load the moveable blocks
	while (loader >> x >> y)
	{
		m_moveBlocks.push_back(new MoveableBlock(world, x, y, scale));
	}
	loader.close();
	loader.open(prefix + "\\pickup.txt"); // Load the pickups
	while (loader >> id >> x >> y)
	{
		if (id == "H")
		{
			m_pickups.push_back(new Pickup(false, true, false, sf::Vector2f(x, y))); // There are three types of pickup
		}
		else if (id == "S")
		{
			m_pickups.push_back(new Pickup(true, false, false, sf::Vector2f(x, y)));
		}
		else
		{
			m_pickups.push_back(new Pickup(false, false, true, sf::Vector2f(x, y)));
		}
	}
	loader.close();
	
	loader.open(prefix + "\\enemies.txt"); // Load the enemies
	while (loader >> id >> x >> y >> xMin >> xMax)
	{
		if (id == "G")
		{
			m_ghosts.push_back(new Ghost(sf::Vector2f(x, y), 3, 100, 250));
		}
		else
		{
			m_enemies.push_back(new Enemy(world, x, y, xMin, xMax, 5, 250, scale));
		}
	}
	loader.close();
	loader.open(prefix + "\\messages.txt");
	while (!loader.eof())
	{
		sf::Text text;
		text.setFont(m_font);
		text.setCharacterSize(40.f);
		std::string s1;
		std::string s2;
		std::string s3;
		std::getline(loader, s1);
		std::getline(loader, s2);
		std::getline(loader, s3);
		int xPos = atoi(s1.c_str());
		int yPos = atoi(s2.c_str());
		text.setPosition(xPos, yPos); // atoi converts c style string to an int
		text.setString(s3);
		m_helpMessages.push_back(text);
	}
	loader.close();

	loader.open(prefix + "\\level.txt"); // Load level geometry
	std::string levelLine;
	int counterY = 0;
	std::stringstream ss;
	while (!loader.eof())
	{
		std::getline(loader, levelLine);
		for (int i = 0; i < levelLine.length(); ++i)
		{
			if (levelLine.at(i) != '0')
			{
				Block * b = new Block(
					world, 
					i * 64, counterY * 64, 
					m_blockMap[std::string(1, levelLine.at(i))].x, 
					m_blockMap[std::string(1, levelLine.at(i))].y, 
					m_blockMap[std::string(1, levelLine.at(i))].destructible, 
					scale);
				m_blocks.push_back(b);
			}
		}
		++counterY;
	}
	loader.close();
	loader.open(prefix + "\\bg.txt"); // Load the background
	std::string s;
	std::getline(loader, s);
	// Setup the background sprites
	m_backgroundSprite1.setTexture(g_resourceManager.m_textureHolder[s]);
	m_backgroundSprite2.setTexture(g_resourceManager.m_textureHolder[s]);
	m_backgroundSprite1.setScale(m_screenWidth / m_backgroundSprite1.getLocalBounds().width, m_screenHeight / m_backgroundSprite1.getLocalBounds().height);
	m_backgroundSprite2.setScale(m_backgroundSprite1.getScale());
	m_backgroundSprite1.setPosition(0, 0);
	m_backgroundSprite2.setPosition(m_backgroundSprite1.getGlobalBounds().width, 0);
	std::getline(loader, s);
	s = "ASSETS\\SHADERS\\" + s;
	sf::Shader & shader = m_game->getShader();
	if (!shader.loadFromFile(s, sf::Shader::Fragment))
	{
		std::cout << "Failed to load shader" << std::endl;
	}
	shader.setUniform("resolution", sf::Vector2f(1920, 1080));

	loader.close();
}

/// <summary>
/// 
/// </summary>
/// <param name="window">We need to get the window position for the background parallax scrolling</param>
/// <param name="windowMovementX">The movement that the window has teaken due to the player movement</param>
/// <param name="t_deltaTime">time since the last update</param>
void Level::update(sf::RenderWindow & window, float windowMovementX, sf::Time t_deltaTime)
{
	// Grt the current locations of the window and background sprites
	float windowX = window.getView().getCenter().x - window.getSize().x / 2.f;
	float windowY = window.getView().getCenter().y - window.getSize().y / 2.f;
	float sprite1X = m_backgroundSprite1.getPosition().x;
	float sprite2X = m_backgroundSprite2.getPosition().x;

	// Swap the sprites around as needed
	if (m_backgroundSprite1.getPosition().x + m_backgroundSprite1.getGlobalBounds().width < windowX)
	{
		sprite1X = m_backgroundSprite2.getPosition().x + m_backgroundSprite2.getGlobalBounds().width;
	}
	else if (m_backgroundSprite2.getPosition().x + m_backgroundSprite2.getGlobalBounds().width < windowX)
	{
		sprite2X = m_backgroundSprite1.getPosition().x + m_backgroundSprite1.getGlobalBounds().width;
	}
	if (m_backgroundSprite1.getPosition().x > windowX + window.getSize().x)
	{
		sprite1X = sprite2X - m_backgroundSprite2.getGlobalBounds().width;
	}
	else if (m_backgroundSprite2.getPosition().x > windowX + window.getSize().x)
	{
		sprite2X = sprite1X - m_backgroundSprite1.getGlobalBounds().width;
	}

	// Move the sprites
	sprite1X -= (int)windowMovementX;
	sprite2X -= (int)windowMovementX;
	m_backgroundSprite1.setPosition(sprite1X, windowY);
	m_backgroundSprite2.setPosition(sprite2X, windowY);


	//destruction code
	for (int i = 0; i < player.getBombs().size(); ++i)
	{
		sf::Vector2f bombPos = player.getBombs().at(i).getOuter().getPosition();
		if (player.getBombs().at(i).isExplode())
		{
			for (int j = 0; j < m_blocks.size(); ++j)
			{
				sf::Vector2f blockPos = m_blocks.at(j)->getSprite().getPosition();
				float distance = sqrt((blockPos.x - bombPos.x) * (blockPos.x - bombPos.x) + (blockPos.y - bombPos.y) * (blockPos.y - bombPos.y));
				if (player.getBombs().at(i).getOuter().getRadius() > distance)
				{
					if (!m_blocks.at(j)->isConcrete())
					{
						m_blocks.at(j)->destroyBody();
					}
				}
			}
			for (auto & ghost : m_ghosts)
			{
				sf::Vector2f ghostPos = ghost->getSprite().getPosition();
				float distance = sqrt((ghostPos.x - bombPos.x) * (ghostPos.x - bombPos.x) + (ghostPos.y - bombPos.y) * (ghostPos.y - bombPos.y));
				if (player.getBombs().at(i).getOuter().getRadius() > distance)
				{
					if (ghost->getState())
					{
						ghost->destroy();
						m_hud->setScore(1000);
					}
				}
			}
			for (auto & enemy : m_enemies)
			{
				sf::Vector2f enemyPos = enemy->getSprite().getPosition();
				float distance = sqrt((enemyPos.x - bombPos.x) * (enemyPos.x - bombPos.x) + (enemyPos.y - bombPos.y) * (enemyPos.y - bombPos.y));
				if (player.getBombs().at(i).getOuter().getRadius() > distance)
				{
					if (enemy->getState())
					{
						enemy->destroy();
						m_hud->setScore(1000);
					}
				}
			}
			player.getBombs().at(i).Explode(false);
		}
	}

	// Update to the total time so far and pass that to the shader
	timer += t_deltaTime.asSeconds();
	m_shader.setUniform("time", timer);

	// Check if the player has reached the end of a level
	if (m_goal->getSprite().getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
	{
		m_game->increaseLevel(); // End Level
		player.silence();
	}

	// Check if the player has died
	if (!player.isPlayerDead())
	{
		std::cout << "player dead" << std::endl;
		m_game->setGameState(GameState::Die);
	}
	// Update the moveable blocks
	for each (MoveableBlock* block in m_moveBlocks)
	{
		block->Update();
	}

	// Check if the player has picked up any pickups
	for each (Pickup* p in m_pickups)
	{
		p->update(t_deltaTime);
		if (p->isAHealth() && p->isColliding(player.getSprite()))
		{
			player.gainHealth();
		}
		if (p->isAScore() && p->isColliding(player.getSprite()))
		{
			player.increaseScore();
		}
		if (p->isABomb() && p->isColliding(player.getSprite()))
		{
			player.increaseBombs();
		}
		p->checkCollision(player.getSprite());
	}

	// Check if the player has killed an enemy
	for each (Enemy * enemy in m_enemies)
	{
		enemy->update(t_deltaTime, player);
		if (player.getHitBox().getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds()) && player.isPlayerAttacking() && enemy->getState())
		{
			enemy->destroy();
			m_hud->setScore(1000);
		}
	}

	// Check if the player has killed a ghost
	for each (Ghost * ghost in m_ghosts)
	{
		ghost->update(t_deltaTime, player);
		if (player.getHitBox().getGlobalBounds().intersects(ghost->getSprite().getGlobalBounds()) && player.isPlayerAttacking() && ghost->getState())
		{
			ghost->destroy();
			m_hud->setScore(1000);
		}
	}
}

/// <summary>
/// Simple render fmethod draws all aspects of the level
/// </summary>
/// <param name="window">Window used to draw all the aspects of a level</param>
void Level::render(sf::RenderWindow & window)
{
	// Draw the backgorund
	window.draw(m_backgroundSprite1);
	window.draw(m_backgroundSprite2);

	// Draw the block geometry
	for (int i = 0; i < m_blocks.size(); i++)
	{
		sf::Vector2f & pos = m_blocks.at(i)->getPos();
		float windowX = window.getView().getCenter().x - window.getSize().x / 2.f;
		float windowY = window.getView().getCenter().y - window.getSize().y / 2.f;
		if (pos.x + 32 > windowX && pos.x - 32 < windowX + window.getSize().x && pos.y + 32 > windowY && pos.y - 32 < windowY + window.getSize().y)
		{
			m_blocks.at(i)->Draw(window);
		}
	}

	m_goal->Draw(window); // Draw the goal

	// Draw all the moveable blocks in a level
	for each (MoveableBlock* block in m_moveBlocks)
	{
		block->Draw(window);
	}

	// Draw all the pickups
	for each(Pickup* p in m_pickups)
	{
		p->draw(window);
	}

	// Draw all the enemies
	for each (Enemy * enemy in m_enemies)
	{
		enemy->draw(window);
	}

	// Draw all the ghosts
	for each (Ghost * ghost in m_ghosts)
	{
		ghost->draw(window);
	}

	// Draw the help messages if present
	for (auto & text : m_helpMessages)
	{
		window.draw(text);
	}
}

// Tagged for deletin *****************************************************************************
void Level::setSoundVolume(float volume)
{
	for each (Enemy * e in m_enemies)
	{
		e->setSoundVolume(volume);
	}
	for each (Ghost * g in m_ghosts)
	{
		g->setSoundVolume(volume);
	}
	for each (Pickup * p in m_pickups)
	{
		p->setMusicVolume(volume);
	}
	player.setSoundVolume(volume);
}
