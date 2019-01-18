#include"CheckBox.h"
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>

//checkbox
CheckBox::CheckBox(std::string s, float x, float y) :
	Widget()
{
	m_id = "checkbox";
	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
		
	}
	m_icon.setFillColor(sf::Color::White);
	m_icon.setOutlineColor(sf::Color::White);
	m_icon.setPosition(x - 20, y + 20);
	m_icon.setScale(2, 2);
	m_icon.setSize(sf::Vector2f(10, 10));
	m_icon.setOutlineThickness(1.3);
	m_isActive = false;
	m_hasFocus = false;

	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition((x + 10), y);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50);

	m_rect.setPosition(x-30 , y);
	m_rect.setSize(sf::Vector2f((m_icon.getGlobalBounds().width + m_text.getGlobalBounds().width) + 30, m_text.getGlobalBounds().height + 15));
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(1);
}

//draw the components of the radiobutton
void CheckBox::draw(sf::RenderWindow &window)
{
	window.draw(m_rect);
	window.draw(m_icon);
	window.draw(m_text);

}

//check focus of the radiobutton
bool CheckBox::checkFocus()
{
	return m_hasFocus;
}

//make it get focus
void CheckBox::getFocus()
{
	m_hasFocus = true;
}

//make it lose focus
void CheckBox::loseFocus()
{
	m_hasFocus = false;
}

//set button to active
void CheckBox::getActive()
{
	m_isActive = true;
}
//set inactive
void CheckBox::loseActive()
{
	m_isActive = false;
}
//update the radio button
void CheckBox::update()
{
	if (m_hasFocus == true)
	{
		m_text.setFillColor(sf::Color::Red);
		m_rect.setOutlineColor(sf::Color::Red);
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
bool CheckBox::checkActive()
{
	return m_isActive;
}
