#include "CreditsScreen.h"

CreditsScreen::CreditsScreen(float width, float height, Game & game, sf::RenderWindow & window):
	m_window(window),
	m_game(&game)
{
	if (!m_font.loadFromFile("Adventurer.ttf"))
	{

	}
	startingPos = sf::Vector2f(300, 600);
	infile.open("credits.txt");
	while (!infile.eof()) // To get you all the lines.
	{
		std::string str;
		getline(infile,str);
		sf::Text t = sf::Text();
		t.setFont(m_font);
		t.setString(str);
		m_texts.push_back(t);
	}
	infile.close();

	m_background.setPosition(0, 0);
	m_background.setSize(sf::Vector2f(1920, 1080));
	m_background.setFillColor(sf::Color::Black);

	for(int i=0; i<m_texts.size(); i++)
	{
		m_texts.at(i).setPosition(startingPos.x, startingPos.y + i * 100);
		m_texts.at(i).setFillColor(sf::Color::White);
		//m_texts.at(i).setScale(2, 2);
		m_texts.at(i).setCharacterSize(60);
	}

	m_texts.at(0).setStyle(sf::Text::Underlined);
	moveUp = sf::Vector2f(0,-2);
	
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::draw()
{
	m_window.draw(m_background);
	for each (sf::Text t in m_texts)
	{
		m_window.draw(t);
	}
	
}

void CreditsScreen::update()
{
	y = moveUp.y;
	for (auto & t : m_texts)
	{
		t.setPosition(t.getPosition().x, t.getPosition().y + y);
	}

	if (m_texts.at(m_texts.size() - 1).getPosition().y < -80)
	{
		goBack();
	}

	
}

void CreditsScreen::goBack()
{
	m_game->setGameState(GameState::MainMenu);
}
