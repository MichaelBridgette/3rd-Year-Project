#include "MainMenu.h"

/*
Created By: Michael Bridgette & David O'Gorman
Date: 02/03/2017
Hours Spent: ~15hours
Summary: A simple sfml game with menu, options that use the common UI elements
*/

//main menu of the game
Menu::Menu(float width, float height, Game & game, sf::RenderWindow &window) :
	m_label("Knight Hunt", (width)- 100, (height / MAX_ITEMS )*0.50f),
	m_game(&game),
	m_window(window)
{
	m_itemSelected = false;
	//m_label.setUnderLined();
	m_label.changeTextSize(200);
	m_widgets[0] = new Button("Play Game", (width/0.60f ), float(height / (MAX_ITEMS-1 ) * 2.0f));
	m_widgets[0]->getFocus();
	m_widgets[0]->Enter = std::bind(&Menu::GoToPlay, this); //func bind
	m_widgets[1] = new Button("Options", (width/0.60f ), (height / (MAX_ITEMS-1) * 2.5));
	m_widgets[1]->Enter = std::bind(&Menu::GoToOptions, this); //func bind
	m_widgets[2] = new Button("Credits", (width/0.60f ), (height / (MAX_ITEMS-1) * 3.0));  //dynamic placements
	m_widgets[2]->Enter = std::bind(&Menu::GoToCredits, this); //bind
	m_widgets[3] = new Button("End Game", (width / 0.60f), (height / (MAX_ITEMS-1 ) * 3.5));  
	m_widgets[3]->Enter = std::bind(&Menu::EndGame, this); //bind
	m_selectedItemIndex = 0; //start at top 

	m_gui.vertical = true; //control scheme

	if (!m_texture.loadFromFile("background.png"))
	{
		//handle
	}

	//m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	//m_background.setFillColor(sf::Color(0, 0, 0, 255));

	m_background.setTexture(m_texture);
	m_background.setPosition(0, 0);

	//add ui elements to gui
	for each (Widget* var in m_widgets)
	{
		m_gui.addWidget(var);
	}
	m_gui.addLabel(&m_label);


}


Menu::~Menu()
{
	for each(Widget* var in m_widgets)
	{
		delete var;
	}
}

/*
Draw the ui elements
*/
void Menu::draw()
{
	m_window.draw(m_background);
	m_gui.draw(m_window);
}

//update ui elements
void Menu::update()
{


	m_gui.update(m_selectedItemIndex, MAX_ITEMS);
	m_xbox.update();

	//if (m_xbox.m_currentState.Y == true && !m_xbox.m_previousState.Y)
	//{
	//	m_game->setGameState(GameState::Help);
	//	std::cout << "You will not get any help" << std::endl;
	//}

}

//return selected item NOTE: not used
bool Menu::itemSelected()
{
	return m_itemSelected;
}

//change gamestate to play
void Menu::GoToPlay()
{
	m_game->loadLevel("level.txt");
	m_game->setGameState(GameState::Transition);
}

void Menu::EndGame()
{
	m_game->endGame();
	//m_game->setGameState(GameState::Credits);
}

void Menu::GoToOptions()
{
	m_game->setGameState(GameState::OptionsMenu);
}

void Menu::GoToCredits()
{
	m_game->setGameState(GameState::Credits);
}
