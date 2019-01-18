#include "GUI.h"
#include<iostream>
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>
bool GUI::useAnim = true;
sf::Clock GUI::m_timeBetweenClicks = sf::Clock::Clock();
//constructor for gui
GUI::GUI()
{
	vertical = false;
	horizontal = false;
	both = false;
	animating = false;	
	
	//if (!m_buffer.loadFromFile("Gui Transition.wav"))
	//{
	//}
	m_buffer = g_resourceManager.m_soundHolder["gui"];
	m_guiSound.setBuffer(m_buffer); //sound effect
	m_guiSound.setVolume(5);
	counter = 0;
}

GUI::~GUI()
{
	for each(Widget* var in m_elements)
	{
		delete var;
	}
	for each (Label* lbl in m_labels)
	{
		delete lbl;
	}
	std::cout << "Widgets Deleted" << std::endl;
}
//add label to container
void GUI::addLabel(Label * label)
{
	m_labels.push_back(label);
}
//add button to container
void GUI::addButton(Button * button)
{
	m_elements.push_back(button);
}
//add slider to container
void GUI::addSlider(Slider *slider)
{
	m_elements.push_back(slider);
}
//add radioButton to container
void GUI::addRadioButton(RadioButton * radioButton)
{
	m_elements.push_back(radioButton);
}

void GUI::addCheckBox(CheckBox * checkBox)
{
	m_elements.push_back(checkBox);
}

//can be used instead of all above adds
void GUI::addWidget(Widget * widget)
{
	m_elements.push_back(widget);
}

//update, where all elements updates are handled
void GUI::update(int &index, int maxItems)
{
	m_xbox.update(); //update controller
	for each (Widget* var in m_elements)
	{
		var->update();           //update the elements
	}


	if (m_elements[index]->getID() == "slider") //if element is a slider the these can be performed
	{
		if (m_xbox.m_currentState.DpadLeft == true || m_xbox.m_currentState.LeftThumbStickLeft==true || m_xbox.m_currentState.RightThumbStickLeft == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_elements[index]->decreaseValue();
			decreaseSliderValue(index);
		}
		if (m_xbox.m_currentState.DpadRight == true || m_xbox.m_currentState.LeftThumbStickRight == true || m_xbox.m_currentState.RightThumbStickRight == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_elements[index]->increaseValue();
			increaseSliderValue(index);
		}
	}
	

	//control schemes
	if (vertical)
	{
		verticalControls(index, maxItems);
	}
	else if (horizontal)
	{
		horizontalControls(index, maxItems);
	}
	else {
		vertAndHorControls(index, maxItems);
	}


	//animation undergoeing
	if (animating)
	{
		m_elements[index]->endAnim(); //play the animation
		if (m_elements[index]->animEnd) 
		{
			animating = false;
			m_elements[index]->animEnd = false; //animation over
			activate(index); //activate callback
		}
	}

}

//draws all the elements to the screen
void GUI::draw(sf::RenderWindow & window)
{

	for each (Label* var in m_labels)
	{
		var->draw(window);
	}

	for each (Widget* var in m_elements)
	{
		var->draw(window);
	}
}

//for moving up a element in the gui
void GUI::moveUp(int &index)
{
		if (index - 1 >= 0)
		{
			m_guiSound.play();
			
			if (m_elements[index - 1]->isActive == false) 
			{
				if (index - 2 >= 0) //skip inactive element
				{
					m_elements[index]->loseFocus();
					index -= 2;
					m_elements[index]->getFocus();
				}
			}
			else
			{
				m_elements[index]->loseFocus();
				index--;
				m_elements[index]->getFocus();
			}
			

		}
}

//for moving down an element in the gui
void GUI::moveDown(int &index, int maxItems)
{
		if (index + 1 < maxItems)
		{
			m_guiSound.play();
			
			if (m_elements[index + 1]->isActive == false)
			{
				if (index + 2 < maxItems) //skip inactive
				{
					m_elements[index]->loseFocus();
					index += 2;
					m_elements[index]->getFocus();
				}
			}
			else
			{
				m_elements[index]->loseFocus();
				index++;
				m_elements[index]->getFocus();
			}
			
		}
}

//alternative for moving up a row of elements
void GUI::moveUp2(int & index)
{
	if (index - 10 >= 0)
	{

		m_guiSound.play();

		if (m_elements[index - 10]->isActive == false)
		{
			
		}
		else
		{
			m_elements[index]->loseFocus();
			index-=10;
			m_elements[index]->getFocus();
		}


	}
}

//alternative for moving down a row of elements
void GUI::moveDown2(int & index, int maxItems)
{
	if (index + 10 < maxItems)
	{
		m_guiSound.play();

		if (m_elements[index + 10]->isActive == false)
		{
		
		}
		else
		{
			m_elements[index]->loseFocus();
			index+=10;
			m_elements[index]->getFocus();
		}

	}
}

//activate the callback of the element
void GUI::activate(int &index)
{
	bool linked = false;

	if (m_elements[index]->getID() == "button")
	{
		try
		{
			//m_guiSound.play();
			m_elements[index]->Enter();
			
		}
		catch (std::bad_function_call)
		{
			std::cout << "Bad Function Call" << std::endl;
		}
	}
	else if (m_elements[index]->getID() == "checkbox")
	{
		if (m_elements[index]->checkActive() == false)
		{
			m_elements[index]->getActive();
			try
			{
				m_elements[index]->Enter();
			}
			catch (std::bad_function_call)
			{
				std::cout << "Bad Function Call" << std::endl;
			}
		}
		else {
			m_elements[index]->loseActive();
			try
			{
				m_elements[index]->Enter();
			}
			catch (std::bad_function_call)
			{
				std::cout << "Bad Function Call" << std::endl;
			}
		}
	}

	else
	{
		for (int i = 0; i < m_elements.size();i++)
		{
			//if linked then deactivate 
			if (m_elements[index]->checkTag() == m_elements[i]->checkTag()&& m_elements[index]->getID() == m_elements[i]->getID())
			{
				m_elements[i]->loseActive();
				linked = true;
			}

			if (m_elements[index]->checkActive() == true && !linked)
			{
				m_elements[index]->loseActive();
			}
			else {
				m_elements[index]->getActive();
				try {
					m_elements[index]->Enter();
				}
				catch (std::bad_function_call)
				{
					std::cout << "Bad Function Call" << std::endl;
				}
			}
		}

		

		


		
	}
}

//use callback functions of slider that are used to increase values
void GUI::increaseSliderValue(int &index)
{
	try {
		m_elements[index]->AdjustAdd();
		m_elements[index]->increaseValue();
	}
	catch (std::bad_function_call)
	{
		std::cout << "Bad Function Call" << std::endl;
	}
}

//use calback functions of slider that are used to decrease values
void GUI::decreaseSliderValue(int &index)
{
	try {
		m_elements[index]->AdjustMinus();
		m_elements[index]->decreaseValue();
	}
	catch (std::bad_function_call)
	{
		std::cout << "Bad Function Call" << std::endl;
	}
}

//vertical control scheme for xbox controller, dpad vertical use only
void GUI::verticalControls(int &index, int maxItems)
{

	if (!animating)
	{
		if (m_xbox.m_currentState.DpadUp == true && !m_xbox.m_previousState.DpadUp || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !move) )
		{
			move = true;
			moveUp(index);
		}
		if (m_xbox.m_currentState.DpadDown == true && !m_xbox.m_previousState.DpadDown || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !move) )
		{
			move = true;
			moveDown(index, maxItems);
		}

		if (m_xbox.m_currentState.LeftThumbStickUp == true && !m_xbox.m_previousState.LeftThumbStickUp )
		{
			//move = true;
			moveUp(index);
		}

		if (m_xbox.m_currentState.LeftThumbStickDown == true && !m_xbox.m_previousState.LeftThumbStickDown)
		{
			//move = true;
			moveDown(index, maxItems);
		}

	
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false && move == true) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ==false)
		{
			move = false;
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == false && move == true) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == false)
		{
			move = false;
		}
	}
	if (m_xbox.m_currentState.A == true && !m_xbox.m_previousState.A || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if (m_elements[index]->getID() == "button"&& useAnim==true)
		{
			animating = true;
		}
		else if(m_elements[index]->getID() == "button"&& useAnim == false) {

			m_timeBetweenClicks.getElapsedTime().asSeconds();
			if (m_timeBetweenClicks.getElapsedTime().asSeconds() > 1)
			{
				activate(index);
				m_timeBetweenClicks.restart();
			}
		}
		if (m_elements[index]->getID() == "radiobutton"|| m_elements[index]->getID() == "checkbox")
		{
			m_timeBetweenClicks.getElapsedTime().asSeconds();
			if (m_timeBetweenClicks.getElapsedTime().asSeconds() > 0.5f)
			{
				activate(index);
				m_timeBetweenClicks.restart();
			}
		}
		
	}
	
}

//horizontal control scheme for xbox controller, dpad horizontal use only
void GUI::horizontalControls(int & index, int maxItems)
{

	if (!animating)
	{

		if (m_xbox.m_currentState.DpadLeft == true && !m_xbox.m_previousState.DpadLeft || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| m_xbox.m_currentState.LeftThumbStickLeft)
		{
			moveUp(index);
		}
		if (m_xbox.m_currentState.DpadRight == true && !m_xbox.m_previousState.DpadRight || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || m_xbox.m_currentState.LeftThumbStickRight)
		{
			moveDown(index, maxItems);
		}
		if (m_xbox.m_currentState.A == true && !m_xbox.m_previousState.A || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			//activate(index);
			if (m_elements[index]->getID() == "button"&& useAnim == true)
			{
				animating = true;
			}
			else if (m_elements[index]->getID() == "button"&& useAnim == false) {

				m_timeBetweenClicks.getElapsedTime().asSeconds();
				if (m_timeBetweenClicks.getElapsedTime().asSeconds() > 1)
				{
					activate(index);
					m_timeBetweenClicks.restart();
				}
			}
			if (m_elements[index]->getID() == "radiobutton" || m_elements[index]->getID() == "checkbox")
			{
				activate(index);
			}
		}
	}
}

//vertical and horizontal control scheme for xbox controller, dpad vertical and horizontal
void GUI::vertAndHorControls(int & index, int maxItems)
{
	if (m_xbox.m_currentState.DpadLeft == true && !m_xbox.m_previousState.DpadLeft || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveUp(index);
	}
	if (m_xbox.m_currentState.DpadRight == true && !m_xbox.m_previousState.DpadRight || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveDown(index, maxItems);
	}
	if (m_xbox.m_currentState.DpadUp == true && !m_xbox.m_previousState.DpadUp || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveUp2(index);
	}
	if (m_xbox.m_currentState.DpadDown == true && !m_xbox.m_previousState.DpadDown || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveDown2(index, maxItems);
	}
	if (m_xbox.m_currentState.A == true && !m_xbox.m_previousState.A || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		activate(index);
	}
}

//clear out all the elements 
void GUI::removeAllElements()
{
	m_elements.clear();
	m_labels.clear();
}






