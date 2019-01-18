#ifndef SPLASH
#define SPLASH

#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Label.h"
#include"XBOX360CONTROLLER.h"
#include "GUI.h"
#include<iostream>
#include"Game.h"

/*
Created By: Michael Bridgette
Known Bugs: none
*/



class Game;

//splash of the game
class Splash
{
public:
	Splash(Game& game, sf::RenderWindow &window);
	~Splash();
	void draw(); //draw
	void update();//update
	void GoToMenu(); 
private:

	Game *m_game;
	sf::RenderWindow &m_window;

	sf::RectangleShape m_background;

	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_text2;
	int counter;

	sf::Vector2f m_pos;

	float backgroundAlpha;
	float textAlpha;
};

#endif // !SPLASH
