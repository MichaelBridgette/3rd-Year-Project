#pragma once
#ifndef CREDITSSCREEN
#define CREDITSSCREEN

#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Label.h"
#include"XBOX360CONTROLLER.h"
#include "GUI.h"
#include<iostream>
#include"Game.h"
#include <fstream>
#include <string>

/*
Created By: Michael Bridgette
Known Bugs: none
*/



class Game;

//main menu of the game
class CreditsScreen
{
public:
	CreditsScreen(float width, float height, Game& game, sf::RenderWindow &window);
	~CreditsScreen();
	void draw(); //draw
	void update();//update
	void goBack(); //end the credits
private:
	int m_selectedItemIndex; //the current item/ menu option

	sf::RectangleShape m_background;
	Game *m_game;
	sf::RenderWindow &m_window;

	sf::Font m_font;

	std::vector<sf::Text> m_texts;
	std::ifstream infile;

	sf::Vector2f startingPos;
	sf::Vector2f moveUp;
	float y;
	float alpha;
};

#endif // !CREDITSSCREEN
