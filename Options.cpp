#include "Options.h"

/*
Created By: Michael Bridgette & David O'Gorman
Date: 02/03/2017
Hours Spent: ~15hours
Summary: A simple sfml game with menu, options that use the common UI elements
*/

//main menu of the game
Options::Options(float width, float height, Game & game, sf::RenderWindow &window) :
	m_label("Options", (width)+200, (height / 3)*0.50f),
	m_game(&game),
	m_window(window)
{
	m_itemSelected = false;
	m_label.setUnderLined();
	m_label.changeTextSize(125);
	volume = 100;
	sfxVolume = 20;
	m_widgets[0] = new Slider((width / 0.65f), float(height / (3 - 0.5f) * 1.50f), volume, "Music", 2.5f);
	m_widgets[0]->AdjustAdd = std::bind(&Options::setMusicVolume, this);
	m_widgets[0]->AdjustMinus = std::bind(&Options::setMusicVolume, this);
	m_widgets[0]->getFocus();

	m_widgets[1] = new Slider((width / 0.65f), float(height / (3 - 0.5f) * 2.00f), sfxVolume, "Sfx", 0.50f);
	m_widgets[1]->AdjustAdd = std::bind(&Options::setSfxVolume, this);
	m_widgets[1]->AdjustMinus = std::bind(&Options::setSfxVolume, this);

	m_widgets[2] = new CheckBox("Shader on/off", (width / 0.65f), float(height / (3 - 0.5f) * 2.50f));
	m_widgets[2]->getActive();
	m_widgets[2]->Enter = std::bind(&Options::AdjustShader, this);

	m_widgets[3] = new Button("Main Menu", (width/.67f), float(height / (3 - 0.5f) * 3.0f),50);
	m_widgets[3]->Enter = std::bind(&Options::GoToMenu, this); //func bind
	//m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	//m_background.setFillColor(sf::Color(0, 0, 0, 255));

	if (!m_texture2.loadFromFile("background.png"))
	{

	}
	m_background.setPosition(0, 0);
	m_background.setTexture(m_texture2);
	m_selectedItemIndex = 0; //start at top 

	m_gui.vertical = true; //control scheme

	

	//add ui elements to gui
	for each (Widget* var in m_widgets)
	{
		m_gui.addWidget(var);
	}
	m_gui.addLabel(&m_label);


}


Options::~Options()
{
	for each(Widget* var in m_widgets)
	{
		delete var;
	}
}

/*
Draw the ui elements
*/
void Options::draw()
{
	m_window.draw(m_background);
	m_gui.draw(m_window);
}

//update ui elements
void Options::update()
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
bool Options::itemSelected()
{
	return m_itemSelected;
}

//change gamestate to play
void Options::GoToPlay()
{
	//m_game->loadLevel("level.txt");
	m_game->setGameState(GameState::Play);
}

void Options::GoToMenu()
{
	m_game->setGameState(GameState::MainMenu);
}

void Options::AdjustShader()
{
	m_game->toggleShader();
}

void Options::setMusicVolume()
{
	volume = m_widgets[0]->getValue();
	m_game->setMusicVolume(volume);
}

void Options::setSfxVolume()
{
	sfxVolume = m_widgets[1]->getValue();
	g_resourceManager.m_soundResourceVolume = sfxVolume;
	//m_game->setSfxVolume(sfxVolume);
}


