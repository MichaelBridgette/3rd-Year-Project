#pragma once
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>
#include<SFML\Graphics.hpp>
#include"Label.h"
#include"Widget.h"
#include<iostream>

//sliders
class Slider: public Widget {

public:
	Slider(float x, float y, float &value, std::string s, float valueChange);

	void getFocus() override; //gain highlight
	void loseFocus() override; //lose highlight
	bool checkFocus()override; //check for focus

	void update()override; //update
	void draw(sf::RenderWindow &window)override; //draw
	int getValue(); //get sliders value
	void increaseValue(); //increase rect length
	void decreaseValue(); //decrease it

private:
	
	sf::RectangleShape m_innerRect; //inner rectangle

	float m_rectX = 180; 
	float m_rectY = 10; 
	float m_val; //slider value
	float maxValue;

	float reduceValue;

	sf::Font m_font;
	sf::Text m_text;

};