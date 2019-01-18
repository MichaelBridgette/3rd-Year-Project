#include "Hud.h"

HUD::HUD()
{
	health = 3;
	bombNum = 3;
	if (!m_font.loadFromFile("Adventurer.ttf"))
	{

	}
	m_scoreText.setFont(m_font);

	if (!m_lifeTexture1.loadFromFile("life1.png"))
	{

	}
	if (!m_lifeTexture2.loadFromFile("life2.png"))
	{
		std::cout << "Life 2 fail" << std::endl;
	}
	if (!m_lifeTexture3.loadFromFile("life3.png"))
	{

	}
	if (!m_lifeTexture4.loadFromFile("life4.png"))
	{

	}

	if (!m_bombTexture.loadFromFile("bomb.png"))
	{

	}
	m_bombSprite.setTexture(m_bombTexture);
	m_bombSprite.setScale(sf::Vector2f(0.30f, 0.30f));
	m_bombCount.setFont(m_font);
	m_bombCount.setFillColor(sf::Color::Yellow);
	m_bombCount.setScale(sf::Vector2f(2, 2));

	m_scoreText.setFont(m_font);
	m_scoreText.setFillColor(sf::Color::Yellow);
	m_scoreText.setScale(sf::Vector2f(1.5, 1.5));

	m_3lifeBar.setTexture(m_lifeTexture1);
	m_2lifeBar.setTexture(m_lifeTexture2);
	m_1lifeBar.setTexture(m_lifeTexture3);
	m_0lifeBar.setTexture(m_lifeTexture4);

	alphaChange = 0.5f;
}

void HUD::update(sf::View playerView)
{
	
	m_3lifeBar.setPosition(playerView.getCenter().x - 925, playerView.getCenter().y - 500);
	m_2lifeBar.setPosition(playerView.getCenter().x - 925, playerView.getCenter().y - 500);
	m_1lifeBar.setPosition(playerView.getCenter().x - 925, playerView.getCenter().y - 500);
	m_0lifeBar.setPosition(playerView.getCenter().x - 925, playerView.getCenter().y - 500);

	m_bombSprite.setPosition(playerView.getCenter().x+750 , playerView.getCenter().y-535 );
	m_bombCount.setPosition(playerView.getCenter().x + 865, playerView.getCenter().y - 505);
	m_bombCount.setString(":"+std::to_string(bombNum));

	m_scoreText.setPosition(playerView.getCenter().x - 925, playerView.getCenter().y - 440);
	m_scoreText.setString("Score: " + std::to_string(score));
	//if (alpha > 0)
	//{
	//	alpha-=5;
	//}
	//m_lifeBar.setColor(sf::Color(m_lifeBar.getColor().r, m_lifeBar.getColor().g, m_lifeBar.getColor().b, alpha));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && press ==false)
	{
		increaseHealth();
		press = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)&&press==false)
	{
		decreaseHealth();
		press = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::U) == false && press == true) && sf::Keyboard::isKeyPressed(sf::Keyboard::P) == false)
	{
		press = false;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::P) == false && press == true) && sf::Keyboard::isKeyPressed(sf::Keyboard::U) == false)
	{
		press = false;
	}
}

void HUD::draw(sf::RenderWindow &m_window)
{
	manageHealthAnimations(m_window);
	m_window.draw(m_bombSprite);
	m_window.draw(m_bombCount);
	m_window.draw(m_scoreText);
}

void HUD::increaseHealth()
{
	if (health < 3 && healthUp == false && healthDown ==false)
	{
		health++;
		healthUp = true;
	}
}

void HUD::decreaseHealth()
{
	if (health > 0 && healthDown ==false && healthUp==false)
	{
		health--;
		healthDown = true;
	}
}

void HUD::setHealth(int num)
{
	health = num;
}

int HUD::getHealth()
{
	return health;
}

int HUD::getBombNum()
{
	return bombNum;
}

void HUD::setBombNum(int num)
{
	bombNum = num;
}

void HUD::setScore(int num)
{
	score += num;
}

void HUD::resetScore()
{
	score = 0;
}

void HUD::increaseBombs()
{
	bombNum++;
}

void HUD::resetBools()
{
	healthUp = false;
	healthDown = false;
}

void HUD::manageHealthAnimations(sf::RenderWindow &m_window)
{
	if (health == 3 && healthUp == false && healthDown == false)
	{
		m_window.draw(m_3lifeBar);

		m_2alpha = 255;
		m_2lifeBar.setColor(sf::Color(m_2lifeBar.getColor().r, m_2lifeBar.getColor().g, m_2lifeBar.getColor().b, m_2alpha));
	}


	else if (health == 3 && healthUp == true && healthDown == false)
	{
		m_window.draw(m_3lifeBar);
		m_window.draw(m_2lifeBar);

		m_2alpha -= alphaChange;
		m_2lifeBar.setColor(sf::Color(m_2lifeBar.getColor().r, m_2lifeBar.getColor().g, m_2lifeBar.getColor().b, m_2alpha));
		if (m_2alpha <= 0)
		{
			healthUp = false;
		}
	}

	else if (health == 2 && healthDown == true && healthUp == false)
	{
		m_window.draw(m_2lifeBar);
		m_window.draw(m_3lifeBar);

		m_3alpha -= alphaChange;
		m_3lifeBar.setColor(sf::Color(m_3lifeBar.getColor().r, m_3lifeBar.getColor().g, m_3lifeBar.getColor().b, m_3alpha));
		if (m_3alpha <= 0)
		{
			healthDown = false;
		}
	}


	else if (health == 2 && healthDown == false && healthUp == false)
	{
		m_3alpha = 255;
		m_1alpha = 255;
		m_3lifeBar.setColor(sf::Color(m_3lifeBar.getColor().r, m_3lifeBar.getColor().g, m_3lifeBar.getColor().b, m_3alpha));
		m_1lifeBar.setColor(sf::Color(m_1lifeBar.getColor().r, m_1lifeBar.getColor().g, m_1lifeBar.getColor().b, m_1alpha));
		m_window.draw(m_2lifeBar);
	}
	else if (health == 2 && healthDown == false && healthUp == true)
	{
		m_window.draw(m_2lifeBar);
		m_window.draw(m_1lifeBar);

		m_1alpha -= alphaChange;
		m_1lifeBar.setColor(sf::Color(m_1lifeBar.getColor().r, m_1lifeBar.getColor().g, m_1lifeBar.getColor().b, m_1alpha));
		if (m_1alpha <= 0)
		{
			healthUp = false;
		}
	}

	else if (health == 1 && healthDown == true && healthUp == false)
	{
		m_window.draw(m_1lifeBar);
		m_window.draw(m_2lifeBar);

		m_2alpha -= alphaChange;
		m_2lifeBar.setColor(sf::Color(m_2lifeBar.getColor().r, m_2lifeBar.getColor().g, m_2lifeBar.getColor().b, m_2alpha));
		if (m_2alpha <= 0)
		{
			healthDown = false;
		}
	}
	else if (health == 1 && healthDown == false && healthUp == true)
	{
		m_window.draw(m_1lifeBar);
		m_window.draw(m_0lifeBar);

		m_0alpha -= alphaChange;
		m_0lifeBar.setColor(sf::Color(m_0lifeBar.getColor().r, m_0lifeBar.getColor().g, m_0lifeBar.getColor().b, m_0alpha));
		if (m_0alpha <= 0)
		{
			healthUp = false;
		}
	}

	else if (health == 1 && healthDown == false && healthUp == false)
	{
		m_2alpha = 255;
		m_0alpha = 255;
		m_2lifeBar.setColor(sf::Color(m_2lifeBar.getColor().r, m_2lifeBar.getColor().g, m_2lifeBar.getColor().b, m_2alpha));
		m_0lifeBar.setColor(sf::Color(m_0lifeBar.getColor().r, m_0lifeBar.getColor().g, m_0lifeBar.getColor().b, m_0alpha));
		m_window.draw(m_1lifeBar);
	}
	else if (health == 0 && healthDown == true && healthUp == false)
	{
		m_window.draw(m_0lifeBar);
		m_window.draw(m_1lifeBar);

		m_1alpha -= alphaChange;
		m_1lifeBar.setColor(sf::Color(m_1lifeBar.getColor().r, m_1lifeBar.getColor().g, m_1lifeBar.getColor().b, m_1alpha));
		if (m_1alpha <= 0)
		{
			healthDown = false;
		}
	}

	else if (health == 0 && healthDown == false && healthUp == false)
	{
		m_1alpha = 255;
		m_1lifeBar.setColor(sf::Color(m_2lifeBar.getColor().r, m_2lifeBar.getColor().g, m_2lifeBar.getColor().b, m_2alpha));
		m_window.draw(m_0lifeBar);
	}
}
