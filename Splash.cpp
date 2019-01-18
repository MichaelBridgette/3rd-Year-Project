#include "Splash.h"

Splash::Splash(Game & game, sf::RenderWindow & window):
	m_window{window},
	m_game{&game}
{
	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}
	m_text.setFont(m_font);
	textAlpha = 255;

	m_text.setFillColor(sf::Color(255, 255, 255, textAlpha));
	m_text.setCharacterSize(200);
	m_pos = sf::Vector2f(m_window.getView().getCenter().x/2, 900);
	m_text.setPosition(m_pos);
	m_text.setString("Knight Hunt");

	m_text2.setFont(m_font);
	m_text2.setCharacterSize(30);
	m_text2.setFillColor(sf::Color(255, 255, 255, textAlpha));
	m_text2.setPosition(1500,1000);
	m_text2.setString("A game by Michael & Liam ©.");

	m_background.setPosition(0, 0);
	m_background.setSize(sf::Vector2f(2160, 3840));
	backgroundAlpha = 255;
	m_background.setFillColor(sf::Color(0, 0, 0, backgroundAlpha));
}

Splash::~Splash()
{
}

void Splash::draw()
{
	m_window.draw(m_background);
	m_window.draw(m_text);
	m_window.draw(m_text2);
}

void Splash::update()
{
	if (m_pos.y > 250)
	{
		m_pos.y-=5;
	}

	if (m_pos.y <= 250)
	{
		if (textAlpha > 0)
		{
			textAlpha-=2.5f;
			m_text.setFillColor(sf::Color(255, 255, 255, textAlpha));
			m_text2.setFillColor(sf::Color(255, 255, 255, textAlpha));
		}
		else if (textAlpha <= 0)
		{
			textAlpha = 0;
			if (backgroundAlpha > 0)
			{
				backgroundAlpha-=2.5f;
				m_background.setFillColor(sf::Color(0, 0, 0, backgroundAlpha));
			}
			else if (backgroundAlpha <= 0)
			{
				backgroundAlpha = 0;
				GoToMenu();
			}
		}
	}
	m_text.setPosition(m_pos);

}

void Splash::GoToMenu()
{
	m_game->setGameState(GameState::MainMenu);
}
