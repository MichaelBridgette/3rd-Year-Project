#include "GameComplete.h"

GameCompleteScreen::GameCompleteScreen(std::string levelName, Game & game, sf::RenderWindow & window):
m_game(&game),
m_window{ window }
{
	transparency = 0;
	transparency2 = 0;
	m_levelName = levelName;
	m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	m_background.setFillColor(sf::Color(0, 0, 0, transparency));
	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;
	}

	m_text.setFont(m_font);
	m_timeText.setFont(m_font);

	m_text.setCharacterSize(100);
	m_text.setString("Congratulations, Game Completed!");
	m_text.setPosition(sf::Vector2f(m_window.getSize().x / 3.5, m_window.getSize().y / 2.5));
	m_text.setFillColor(sf::Color(255, 255, 255, transparency));
	timer = 0;

	m_timeText.setCharacterSize(50);
	//m_timeText.setStyle(sf::Text::Italic);
	m_timeString = "Returning to Menu in: ";
	m_timeText.setString(m_timeString);
	m_timeText.setPosition(sf::Vector2f(m_window.getSize().x / 4, m_window.getSize().y));
	m_timeText.setFillColor(sf::Color(255, 255, 255, 0));
}

void GameCompleteScreen::draw()
{
	m_window.draw(m_background);
	m_window.draw(m_text);
	m_window.draw(m_timeText);
}

void GameCompleteScreen::update()
{
	if (transparency < 255)
	{
		transparency++;
		m_background.setFillColor(sf::Color(0, 0, 0, transparency));
		m_text.setFillColor(sf::Color(255, 255, 255, transparency));
		sf::Vector2f halfScale(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
		m_background.setPosition(m_window.getView().getCenter() - halfScale);
		m_text.setPosition(m_window.getView().getCenter() + sf::Vector2f(-750, -150));
		m_timeText.setString("");
	}
	else
	{

		timer++;
		m_timeText.setString("Returning to Menu in: " + std::to_string((210 - timer) / 60));
		if (transparency2 < 255)
		{
			transparency2 += 5;

			m_timeText.setPosition(m_window.getView().getCenter() + sf::Vector2f(-250, 0));
			m_timeText.setFillColor(sf::Color(255, 255, 255, transparency2));
		}
		if (timer > 180)
		{

			m_window.setView(m_window.getDefaultView());
			m_game->setGameState(GameState::MainMenu);
			timer = 0;
			transparency = 0;
			transparency2 = 0;
			m_background.setFillColor(sf::Color(0, 0, 0, transparency));
			m_text.setFillColor(sf::Color(255, 255, 255, transparency));
			m_timeText.setFillColor(sf::Color(255, 255, 255, transparency2));
			m_game->loadLevel("level.txt");
		}

	}
}
