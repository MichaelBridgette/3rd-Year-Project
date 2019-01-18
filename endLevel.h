
#pragma once
#ifndef ENDLEVEL
#define ENDLEVEL

#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Label.h"
#include"XBOX360CONTROLLER.h"
#include "GUI.h"
#include<iostream>
#include"Game.h"
#include <string>

class Game;

class EndLevelScreen {
public:
	EndLevelScreen(std::string levelName,Game& game, sf::RenderWindow &window);
	void draw(); //draw
	void update();//update
private:
	sf::RenderWindow &m_window;
	std::string m_levelName;
	sf::RectangleShape m_background;

	sf::Text m_text;
	sf::Font m_font;
	Game *m_game;
	int transparency;
	int transparency2;
	int timer;
	std::string m_timeString;
	sf::Text m_timeText;
};




#endif // !ENDLEVEL