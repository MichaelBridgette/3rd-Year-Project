#pragma once
#ifndef PAUSE
#define PAUSE

#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Label.h"
#include"XBOX360CONTROLLER.h"
#include "GUI.h"
#include<iostream>
#include"Game.h"
#include"XBOX360CONTROLLER.h"
#define MAX_ITEMS 2  //the amount of menu options
/*
Created By: Michael Bridgette
Known Bugs: none
*/



class Game;

//main menu of the game
class Pause
{
public:
	Pause(float width, float height, Game& game, sf::RenderWindow &window);
	~Pause();
	void draw(); //draw
	void update();//update
	void GoToPlay(); //go to playing state
	void EndGame(); //end the game
	void resetPosition();
private:
	int m_selectedItemIndex; //the current item/ menu option
	Widget  * m_widgets[MAX_ITEMS];
	sf::RectangleShape m_background;
	bool m_itemSelected; //what is selected
	GUI m_gui; //gui
	Game *m_game;
	sf::RenderWindow &m_window;
	int transparency;
	Xbox360Controller m_xbox;

};

#endif // !MENU
