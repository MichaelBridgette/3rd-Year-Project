#include "Game.h"

static const float SCALE = 30.f;

/// <summary>
/// Game constructor function, creates a window and sets up Box2D
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1920, 1080, 32 }, "SFML Game",sf::Style::Default},
	m_exitGame{false}, // When true game will exit
	Gravity{0,90.81},
	World{Gravity}//,
	//player{ new Player(World, 200.f, 100.f, SCALE) }
	
{
	g_resourceManager.loadAssets();
	player = new Player(World, 200.f, 100.f, SCALE, &m_hud);
	m_level = new Level(m_window.getSize().x, m_window.getSize().y, *player, time(0), *this, &m_hud);
	//m_level->load("level.txt", World, SCALE);
	m_gameState = GameState::TheSplash;

	m_menu = new Menu(m_window.getSize().x / 4, m_window.getSize().y / 2, *this, m_window);
	m_options = new Options(m_window.getSize().x / 4, m_window.getSize().y / 2, *this, m_window);
	m_endLevelScreen = new EndLevelScreen("Tutorial", *this, m_window);
	m_pauseScreen = new Pause(m_window.getSize().x / 4, m_window.getSize().y / 2, *this, m_window);
	m_credits = new CreditsScreen(0.0f, 0.0f, *this, m_window);
	m_gameComplete = new GameCompleteScreen("", *this, m_window);
	m_die = new DieScreen(m_window.getSize().x / 4, m_window.getSize().y / 2, *this, m_window);
	m_fade = new FadeScreen(*this, m_window);
	m_splash = new Splash(*this, m_window);
	m_music.openFromFile("GameMusic2.wav");
	m_music.setLoop(true);
	m_music.setVolume(100);
	m_music.play();
	
	blankShaderTexture.loadFromFile("test.png");
	blankShaderSprite.setTexture(blankShaderTexture);
	blankShaderSprite.setScale(m_window.getSize().x / blankShaderSprite.getGlobalBounds().width, m_window.getSize().y / blankShaderSprite.getGlobalBounds().height);
	blankShaderSprite.setPosition(sf::Vector2f(0, 0));
	shaderOn = true;
}

/// <summary>
/// Game destructor function (empty)
/// </summary>
Game::~Game() 
{
	delete player;
	delete m_level;
	//delete m_menu;
	//delete m_options;
	//delete m_endLevelScreen;
	//delete m_pauseScreen;
	//delete m_credits;
	//delete m_gameComplete;
	//delete m_die;
	//delete m_fade;
	//delete m_splash;
}

/// <summary>
/// Run method is basic game loop for the game
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // As many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // At least 60 fps
			update(timePerFrame); // 60 fps
			counter += timePerFrame.asSeconds();
			m_shader.setUniform("time", counter);
		}
		render(); // as many as possible
	}
}

void Game::setGameState(GameState gameState)
{
	m_gameState = gameState;
}

void Game::loadLevel(std::string levelName)
{
	m_level->load(m_currentLevel, World, SCALE);
}

void Game::endGame()
{
	m_window.close();
}

void Game::setMusicVolume(float volume)
{
	m_music.setVolume(volume);
}

void Game::setSfxVolume(float volume)
{
	m_level->setSoundVolume(volume);
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_window.close();
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	// Declarations before the switch statement
	sf::View playerView;
	sf::Vector2f playerPos;
	sf::Vector2f viewLoc;
	sf::Vector2f jump;

	switch (m_gameState) {
		case GameState::MainMenu:
			m_window.setView(m_window.getDefaultView());
			m_menu->update();
			break;
		case GameState::Play:
			World.Step(1 / 60.f, 10, 5); // Update the box2d world
			player->Update(t_deltaTime); // Update the player
			for (int i = 0; i < player->getBombs().size(); ++i)
			{
				player->getBombs().at(i).Update(t_deltaTime);
			}
			viewLoc = sf::Vector2f(0, 0);
			viewLoc = m_window.getView().getCenter();
			playerPos = player->getPos();

			jump = (playerPos - viewLoc) * 0.035f; // Acceleration for the camera
			viewLoc += jump; // Constantly adding this to the view location

			// Reset the game attributes etc. based on the new view location
			playerView.setCenter(viewLoc);
			playerView.setSize(m_window.getView().getSize());
			m_window.setView(playerView);
			m_level->update(m_window, jump.x, t_deltaTime);
			blankShaderSprite.setPosition(sf::Vector2f(m_window.getView().getCenter().x - m_window.getView().getSize().x / 2, m_window.getView().getCenter().y - m_window.getView().getSize().y / 2));
			m_hud.update(playerView);

			m_xbox.update();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)|| m_xbox.m_currentState.Start == true&& !m_xbox.m_previousState.Start)
			{
				m_gameState = GameState::PauseScreen;
				m_pauseScreen->resetPosition();
				player->silence();
			}
			break;

		case GameState::EndLevel:
			m_endLevelScreen->update();
			break;
		case GameState::EndGame:
			m_gameComplete->update();
			break;
		case GameState::OptionsMenu:
			m_options->update();
			break;
		case GameState::PauseScreen:
			m_pauseScreen->update();
			break;

		case GameState::Credits:
			m_credits->update();
			break;
		case GameState::Transition:
			if (m_fade->getTransparency() > 0 && m_fade->isFading() == false)
			{
				World.Step(1 / 60.f, 10, 5); // Update the box2d world
				player->Update(t_deltaTime); // Update the player
				for (int i = 0; i < player->getBombs().size(); ++i)
				{
					player->getBombs().at(i).Update(t_deltaTime);
				}
				viewLoc = sf::Vector2f(0, 0);
				viewLoc = m_window.getView().getCenter();
				playerPos = player->getPos();

				jump = (playerPos - viewLoc) * 0.035f; // Acceleration forthe camera
				viewLoc += jump; // Constantly adding this to the view location

								 // Reset the game attributes etc. based on the new view location
				playerView.setCenter(viewLoc);
				playerView.setSize(m_window.getView().getSize());
				m_window.setView(playerView);
				m_level->update(m_window, jump.x, t_deltaTime);
				blankShaderSprite.setPosition(sf::Vector2f(m_window.getView().getCenter().x - m_window.getView().getSize().x / 2, m_window.getView().getCenter().y - m_window.getView().getSize().y / 2));
				m_hud.update(playerView);

				/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					m_gameState = GameState::PauseScreen;
					m_pauseScreen->resetPosition();
					player->silence();
				}*/
			}
			m_fade->update();
			break;
		case GameState::Die:
			m_die->update();
			break;
		case GameState::TheSplash:
			m_splash->update();
			break;
	}

	
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White); // Clear screen

	switch (m_gameState) 
	{
	case GameState::MainMenu:
		m_menu->draw();
		
		break;
	case GameState::Play:
		m_level->render(m_window); // Draw level elements
		
		player->Draw(m_window); // Draw the player
		for (int i = 0; i < player->getBombs().size(); ++i)
		{
			player->getBombs().at(i).Draw(m_window);
		}
		if (shaderOn)
		{
			m_window.draw(blankShaderSprite, &m_shader);
		}
		m_hud.draw(m_window);
		break;

	case GameState::EndLevel:
		m_level->render(m_window); // Draw level elements

		player->Draw(m_window); // Draw the player
		for (int i = 0; i < player->getBombs().size(); ++i)
		{
			player->getBombs().at(i).Draw(m_window);
		}
		if (shaderOn)
		{
			m_window.draw(blankShaderSprite, &m_shader);
		}
		m_endLevelScreen->draw();
		break;
	case GameState::EndGame:
		m_level->render(m_window); // Draw level elements

		player->Draw(m_window); // Draw the player
		for (int i = 0; i < player->getBombs().size(); ++i)
		{
			player->getBombs().at(i).Draw(m_window);
		}
		if (shaderOn)
		{
			m_window.draw(blankShaderSprite, &m_shader);
		}
		m_gameComplete->draw();
		break;
	case GameState::PauseScreen:
		m_level->render(m_window); // Draw level elements

		player->Draw(m_window); // Draw the player
		for (int i = 0; i < player->getBombs().size(); ++i)
		{
			player->getBombs().at(i).Draw(m_window);
		}
		if (shaderOn)
		{
			m_window.draw(blankShaderSprite, &m_shader);
		}
		m_pauseScreen->draw();
		break;
	case GameState::OptionsMenu:
		m_options->draw();
		break;
	case GameState::Credits:
		m_credits->draw();
		break;

	case GameState::Transition:
		if (m_fade->getTransparency() < 255&& m_fade->isFading())
		{
			m_menu->draw();
		}
		if (m_fade->getTransparency() > 0 && m_fade->isFading() == false)
		{
			m_level->render(m_window); // Draw level elements

			player->Draw(m_window); // Draw the player
			for (int i = 0; i < player->getBombs().size(); ++i)
			{
				player->getBombs().at(i).Draw(m_window);
			}
			if (shaderOn)
			{
				m_window.draw(blankShaderSprite, &m_shader);
			}
			m_hud.draw(m_window);
		}
		m_fade->draw();
		break;
	case GameState::Die:
		m_level->render(m_window); // Draw level elements

		player->Draw(m_window); // Draw the player
		for (int i = 0; i < player->getBombs().size(); ++i)
		{
			player->getBombs().at(i).Draw(m_window);
		}
		if (shaderOn)
		{
			m_window.draw(blankShaderSprite, &m_shader);
		}
		m_die->draw();
		break;
	case GameState::TheSplash:
		m_menu->draw();
		m_splash->draw();
		break;
	}
	m_window.display();
}

void Game::increaseLevel()
{
	if (m_currentLevel == m_totalLevels)
	{
		m_currentLevel = 1;
		setGameState(GameState::EndGame);
	}
	else
	{
		++m_currentLevel;
		setGameState(GameState::EndLevel);
	}
}

sf::Shader & Game::getShader()
{
	return m_shader;
}

void Game::toggleShader()
{
	shaderOn= !shaderOn;
}
