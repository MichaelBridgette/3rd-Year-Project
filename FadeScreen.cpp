#include "FadeScreen.h"

FadeScreen::FadeScreen(Game & game, sf::RenderWindow & window):
	m_game{&game},
	m_window{window}
{
	transparency = 0;
	transparency2 = 0;
	m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	m_background.setFillColor(sf::Color(0, 0, 0, transparency));

	timer = 0;
	fadingIn = true;

}

void FadeScreen::draw()
{
	m_window.draw(m_background);
}

void FadeScreen::update()
{

	//m_window.setView(m_window.getDefaultView());
	sf::Vector2f halfScale(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
	m_background.setPosition(m_window.getView().getCenter() - halfScale);
	if (transparency < 255 && fadingIn == true)
	{
		transparency+=5;
		m_background.setFillColor(sf::Color(0, 0, 0, transparency));

	}
	else
	{
		fadingIn = false;
		m_background.setFillColor(sf::Color(0, 0, 0, transparency));
	}

	if (transparency > 0 && fadingIn == false)
	{
		transparency -= 5;
		m_background.setFillColor(sf::Color(0, 0, 0, transparency));
		sf::Vector2f halfScale(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
		m_background.setPosition(m_window.getView().getCenter() - halfScale);
	}
	if(transparency<=0 && fadingIn==false)
	{
		transparency = 0;
		m_background.setFillColor(sf::Color(0, 0, 0, transparency));
		fadingIn = true;
		m_game->setGameState(GameState::Play);
	}
	m_background.setPosition(m_window.getView().getCenter() - halfScale);

}

int FadeScreen::getTransparency()
{
	return transparency;
}

bool FadeScreen::isFading()
{
	return fadingIn;
}
