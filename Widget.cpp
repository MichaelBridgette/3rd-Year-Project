#include"Widget.h"
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>

//widget base class, mostly virtual functions
Widget::Widget()
{
	isActive = true;
}
//widget get focus
void Widget::getFocus()
{
	m_hasFocus = true;
}
//widget lose focus
void Widget::loseFocus()
{
	m_hasFocus = false;
}
//check focus
bool Widget::checkFocus()
{
	return m_hasFocus;
}
//update loop
void Widget::update()
{
	

}
//draw loop
void Widget::draw(sf::RenderWindow &window)
{
	

}

//make widget active 
void Widget::getActive()
{
}
//lose widget active
void Widget::loseActive()
{
}
//check if widget is active
bool Widget::checkActive()
{
	return m_hasFocus;
}
//return id of the widget
std::string Widget::getID()
{
	return m_id;
}
//decrease the widgets value
void Widget::decreaseValue()
{

}
//set the widgets rectangle color
void Widget::setRectColor(sf::Color color)
{
}
//activate callback function
void Widget::activateCallBack()
{
	Enter();
}
//update the widgets text
void Widget::updateText(std::string s)
{
}
//check the tag of the widget
std::string Widget::checkTag()
{
	return m_tag;
}
//change the widgets text size
void Widget::changeTextSize(int size)
{
}
void Widget::updatePosition(sf::Vector2f pos)
{
}
void Widget::updateFocusColor(sf::Color col)
{
}
//animation for the widget
void Widget::endAnim()
{
}
int Widget::getValue()
{
	return 0;
}
//increase the value of the widget
void Widget::increaseValue()
{

}