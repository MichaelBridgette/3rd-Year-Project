#pragma once
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>
#include<SFML\Graphics.hpp>
#include<functional>


//base class for all the UI elements
//nearly all functions will be virtual
class Widget {

public:
	Widget();
	virtual void getFocus(); //gain highlight
	virtual void loseFocus(); //lose highlight
	virtual bool checkFocus(); //check for focus

	virtual void update(); //update

	virtual void getActive();
	virtual void loseActive();
	virtual bool checkActive(); //check if active

	virtual void draw(sf::RenderWindow &window); //draw
	std::string getID(); //check the UI elements ID

	virtual void increaseValue();
	virtual void decreaseValue(); //for sliders

	virtual void setRectColor(sf::Color color); //change rectangle color

	void activateCallBack();

	virtual void updateText(std::string s); //update text of an element

	std::string checkTag(); //check tag, mainly useful in match game gameplay

	virtual void changeTextSize(int size); //adjust text size

	virtual void updatePosition(sf::Vector2f pos);
	virtual void updateFocusColor(sf::Color col);

	typedef std::function<void()> Callback; 
	Callback Enter;
	Callback AdjustAdd;
	Callback AdjustMinus; //callback functions

	bool isActive; //is element active
	virtual void endAnim(); //animation
	bool animEnd; //bool to signify animation is over

	virtual int getValue();
protected:
	sf::RectangleShape m_rect; //rectangle surrounding the element
	bool m_hasFocus; //bool for focus
	std::string m_id; //id of the element eg(button, slider, etc)
	std::string m_tag; //tag of element, can be any word, useful for pairing elements
	
	
};