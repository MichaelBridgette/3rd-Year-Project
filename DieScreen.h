#ifndef DIESCREEN
#define DIESCREEN

#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Label.h"
#include"XBOX360CONTROLLER.h"
#include "GUI.h"
#include<iostream>
#include"Game.h"

#define MAX_ITEMS 2  //the amount of menu options
/*
Created By: Michael Bridgette
Known Bugs: none
*/



class Game;

//main menu of the game
class DieScreen
{
public:
	DieScreen(float width, float height, Game& game, sf::RenderWindow &window);
	~DieScreen();
	void draw(); //draw
	void update();//update
	void EndGame(); //end the game
	void tryAgain();
private:
	int m_selectedItemIndex; //the current item/ menu option
	Widget  * m_widgets[MAX_ITEMS];
	sf::RectangleShape m_background;
	bool m_itemSelected; //what is selected
	GUI m_gui; //gui
	Game *m_game;
	sf::RenderWindow &m_window;
	float transparency;
	float transparency2;
	sf::Text m_text;
	sf::Font m_font;
	int m_count;
};

#endif // !DIESCREEN

