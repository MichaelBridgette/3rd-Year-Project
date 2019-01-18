#pragma once
#ifndef OPTIONS
#define OPTIONS

#include<SFML\Graphics.hpp>
#include"Button.h"
#include"Label.h"
#include"Slider.h"
#include"XBOX360CONTROLLER.h"
#include "GUI.h"
#include<iostream>
#include"Game.h"
#include"ResourceManager.h"

#define MAX_ITEMS 4  //the amount of menu options
/*
Created By: Michael Bridgette
Known Bugs: none
*/
class Game;

//main menu of the game
class Options
{
public:
	Options(float width, float height, Game& game, sf::RenderWindow &window);
	~Options();
	void draw(); //draw
	void update();//update
	bool itemSelected(); //item selected
	void GoToPlay(); //go to playing state
	void GoToMenu();
	void EndGame(); //end the game
	void GoToOptions(); //go to options menu

	void AdjustShader();

	void setMusicVolume();
	void setSfxVolume();

private:
	int m_selectedItemIndex; //the current item/ menu option

	Widget  * m_widgets[MAX_ITEMS];
	Label m_label;
	//Label *m_icon[3]; //ui elements

	sf::Texture m_texture;
	sf::Sprite m_sprite; //background 

	Xbox360Controller m_xbox; //xbox controller
	bool m_itemSelected; //what is selected
	GUI m_gui; //gui
	Game *m_game;
	sf::RenderWindow &m_window;
	float volume;
	float sfxVolume;
	sf::Sprite m_background;
	sf::Texture m_texture2;
};

#endif // !OPTIONS

