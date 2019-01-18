#include"RadioButton.h"
/*
Created By: Michael Bridgette & David O'Gorman
Date: 02/03/2017
Hours Spent: ~15hours
Summary: A simple sfml game with menu, options that use the common UI elements
*/

//radioButton
RadioButton::RadioButton(std::string s, float x, float y, std::string tag) :
	Widget()
{
	m_id = "radiobutton";
	m_tag = tag;
	m_icon.setFillColor(sf::Color::Black);
	m_icon.setOutlineColor(sf::Color::Black);
	m_icon.setPosition(x - 5, y + 10);
	m_icon.setScale(2, 2);
	m_icon.setRadius(3);
	m_icon.setOutlineThickness(1.3);
	m_isActive = false;
	m_hasFocus = false;
	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
		//error message
	}
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition((x + 10), y);
	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(25);

	m_rect.setPosition(x - 10, y);
	m_rect.setSize(sf::Vector2f((m_icon.getGlobalBounds().width + m_text.getGlobalBounds().width) + 10, m_text.getGlobalBounds().height + 15));
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(1);
}

//draw the components of the radiobutton
void RadioButton::draw(sf::RenderWindow &window)
{
	window.draw(m_rect);
	window.draw(m_icon);
	window.draw(m_text);

}

//check focus of the radiobutton
bool RadioButton::checkFocus()
{
	return m_hasFocus;
}

//make it get focus
void RadioButton::getFocus()
{
	m_hasFocus = true;
}

//make it lose focus
void RadioButton::loseFocus()
{
	m_hasFocus = false;
}

//set button to active
void RadioButton::getActive()
{
	m_isActive = true;
}
//set inactive
void RadioButton::loseActive()
{
	m_isActive = false;
}
//update the radio button
void RadioButton::update()
{
	if (m_hasFocus == true)
	{
		m_text.setFillColor(sf::Color::Magenta);
		m_rect.setOutlineColor(sf::Color::Magenta);
	}
	else {
		m_text.setFillColor(sf::Color::Black);
		m_rect.setOutlineColor(sf::Color::Transparent);
	}

	if (m_isActive) //if active fill the circle
	{
		m_icon.setFillColor(sf::Color::Black);

	}
	else {
		m_icon.setFillColor(sf::Color::White);
	}

}
//check for active
bool RadioButton::checkActive()
{
	return m_isActive;
}