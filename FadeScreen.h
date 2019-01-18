#ifndef FADESCREEN
#define FADESCREEN

#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Label.h"
#include"XBOX360CONTROLLER.h"
#include "GUI.h"
#include<iostream>
#include"Game.h"
#include <string>

class Game;

class FadeScreen {
public:
	FadeScreen(Game& game, sf::RenderWindow &window);
	void draw(); //draw
	void update();//update

	int getTransparency();
	bool isFading();
private:
	sf::RenderWindow &m_window;
	sf::RectangleShape m_background;
	Game *m_game;
	int transparency;
	int transparency2;
	int timer;

	bool fadingIn;
};




#endif // !FADESCREEN
