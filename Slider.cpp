#include"Slider.h"

/// <summary>
/// @mainpage Joint Project - 2D racing game.
#include"Slider.h"

/*
Created By: Michael Bridgette & David O'Gorman
Date: 02/03/2017
Hours Spent: ~15hours
Summary: A simple sfml game with menu, options that use the common UI elements
*/

//slider ui element
Slider::Slider(float x, float y, float &value, std::string s, float valueChange) :
	Widget()
{
	reduceValue = valueChange;
	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
		//error message
	}
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition(x - 30, y +15);
	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(50);

	m_val = value;
	m_id = "slider";
	m_hasFocus = false;
	//outer rectangle
	m_rect.setPosition(x + (m_text.getGlobalBounds().width), y+30);
	m_rect.setSize(sf::Vector2f(400.0f, 40.0f));
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(5);

	//inner rectangle, size dictacted by a value
	m_innerRect.setPosition(x + (m_text.getGlobalBounds().width)+10 , y+33 );
	m_innerRect.setSize(sf::Vector2f(m_rect.getSize().x*0.95, m_rect.getSize().y*0.85));
	m_innerRect.setFillColor(sf::Color::White);
	m_innerRect.setOutlineColor(sf::Color::Black);
	m_innerRect.setOutlineThickness(1);

	maxValue = m_val;

}

//make slider get focus
void Slider::getFocus()
{
	m_hasFocus = true;
}
//make it lose focus
void Slider::loseFocus()
{
	m_hasFocus = false;
}

//check its current focus
bool Slider::checkFocus()
{
	return m_hasFocus;
}

//decrease the size of the rectangle
void Slider::decreaseValue()
{
	if (m_val > 0)
	{
		m_val-=reduceValue;
	}
}
//increase the size of the rectangle
void Slider::increaseValue()
{
	if (m_val < maxValue)
	{
		m_val+=reduceValue;
	}
}

//draw the components of the slider
void Slider::draw(sf::RenderWindow &window)
{
	window.draw(m_rect);
	window.draw(m_innerRect);
	window.draw(m_text);

}
//return value that represents the slider
int Slider::getValue()
{
	return m_val;
}

//update the slider component
void Slider::update()
{

	m_innerRect.setSize(sf::Vector2f((m_rect.getSize().x*0.95)*(m_val / maxValue), (m_rect.getSize().y*0.85))); //chaneg the rectangles size based on the value


	if (m_hasFocus == true)
	{

		m_rect.setOutlineColor(sf::Color::Red);
	}
	else
	{
		m_rect.setOutlineColor(sf::Color::Black);
	}

}
