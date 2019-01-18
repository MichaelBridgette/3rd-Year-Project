#include"Button.h"
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>


//constructor
Button::Button(std::string s="", float x=0, float y=0):
	  Widget()
{
	isActive = true; //starts active

	m_id = "button";

	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
	}

	m_hasFocus = false; //no focus
	m_text.setFont(m_font); 
	m_text.setString(s);
	m_text.setPosition(x, y);
	sf::Text testText;
	testText.setFont(m_font);
	testText.setString("|ph");
	testText.setCharacterSize(50);
	//m_text.setOrigin(x/y,y/2);
	m_text.setFillColor(sf::Color::Black); //no focus means element is white
	m_text.setCharacterSize(50);
	m_rect.setPosition(x - 5, y);
	m_rect.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 15, testText.getGlobalBounds().height + 20)); //dynamic rectangle sizing based on text
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Black); //set to transparent
	m_rect.setOutlineThickness(5);
	animEnd = false;
	posX = 0;
	scale = 1;
	focusColor = sf::Color::Red;
}

Button::Button(std::string s, float x, float y, int size)
{
	isActive = true; //starts active

	m_id = "button";

	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
	}

	m_hasFocus = false; //no focus
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition(x, y);
	sf::Text testText;
	testText.setFont(m_font);
	testText.setString("|ph");
	testText.setCharacterSize(size);
	//m_text.setOrigin(x/y,y/2);
	m_text.setFillColor(sf::Color::Black); //no focus means element is white
	m_text.setCharacterSize(size);
	m_rect.setPosition(x - 5, y);
	m_rect.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 15, testText.getGlobalBounds().height + 20)); //dynamic rectangle sizing based on text
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Black); //set to transparent
	m_rect.setOutlineThickness(5);
	animEnd = false;
	posX = 0;
	scale = 1;
	focusColor = sf::Color::Red;
}


//alternative constructor that incorporates tags
Button::Button(std::string s, float x, float y, sf::Color color, std::string tag)
{
	isActive = true;
	m_tag = tag;
	m_id = "button";
	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
		//error message
	}
	m_hasFocus = false;
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition(x, y);
	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(75);

	m_rect.setPosition(x - 5, y);
	m_rect.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 10, m_text.getGlobalBounds().height + 15));
	m_rect.setFillColor(color);
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(4);
	animEnd = false;
	focusColor = sf::Color::Red;
}

Button::~Button()
{
}

//get focus on this element
void Button::getFocus()
{
	
	m_hasFocus = true;
}
//lose focus on this element
void Button::loseFocus()
{
	m_hasFocus = false;
}
//check elements focus
bool Button::checkFocus()
{
	return m_hasFocus;
}

//update loop
void Button::update()
{
	if (m_hasFocus == true&& isActive==true)   
	{
		m_text.setFillColor(focusColor);
		m_rect.setOutlineColor(focusColor);     //turn magenta if the button has focus
	}
	else
	{
		m_text.setFillColor(sf::Color::Black);
		m_rect.setOutlineColor(sf::Color::Black); //back to normal if it doesnt
	}
}
//draw button
void Button::draw(sf::RenderWindow &window)
{
	if (isActive == true)
	{
		window.draw(m_text);
		window.draw(m_rect);
	}
	
}
//change color of rectangle
void Button::setRectColor(sf::Color color)
{
	m_rect.setFillColor(color);
}

//button animation
//button will do a 360 spin before callback is executed
void Button::endAnim()
{	
	/*posX += 10;
	m_text.setRotation(posX);
		
	if (posX >= 360)
	{
		animEnd = true;
		posX = 0;
	}*/

	scale -= 0.05;
	m_text.setScale(scale, scale);
	m_rect.setScale(scale, scale);
	if (scale < 0)
	{
		animEnd = true;
		scale = 1;
		
		m_text.setScale(scale, scale);
		m_rect.setScale(scale, scale);
	}
}

void Button::changeTextSize(int size)
{
	m_text.setCharacterSize(size);
}

void Button::updatePosition(sf::Vector2f pos)
{
	m_text.setPosition(pos.x, pos.y);
	m_rect.setPosition(pos.x - 5, pos.y);
}

void Button::updateFocusColor(sf::Color col)
{
	focusColor = col;
}


