#pragma once
#ifndef MENU
#define MENU

#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Label.h"
#include"XBOX360CONTROLLER.h"
#include "GUI.h"
#include<iostream>
#include"Game.h"

#define MAX_ITEMS 4  //the amount of menu options
/*
Created By: Michael Bridgette
Known Bugs: none
*/



class Game;

//main menu of the game
class Menu
{
public:
	Menu(float width, float height, Game& game, sf::RenderWindow &window);
	~Menu();
	void draw(); //draw
	void update();//update
	bool itemSelected(); //item selected
	void GoToPlay(); //go to playing state
	void EndGame(); //end the game
	void GoToOptions(); //go to options menu
	void GoToCredits();
private:
	int m_selectedItemIndex; //the current item/ menu option

	Widget  * m_widgets[MAX_ITEMS];
	Label m_label;
	//Label *m_icon[3]; //ui elements

	sf::Texture m_texture;
	sf::Sprite m_sprite; //background 
	sf::Sprite m_background;
	Xbox360Controller m_xbox; //xbox controller
	bool m_itemSelected; //what is selected
	GUI m_gui; //gui
	Game *m_game;
	sf::RenderWindow &m_window;
};

#endif // !MENU
