#include "XBOX360CONTROLLER.h"
#include<iostream>

/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>

Xbox360Controller::Xbox360Controller() {}

Xbox360Controller::~Xbox360Controller() {}

/*will check for button presses within this method, get axis positions for both triggers,
get vector coords for both of the thumbsticks and will distinguish which dpad bools should
be true based on their axis coords*/
void Xbox360Controller::update()
{	
	m_previousState = m_currentState;
	//face buttons
	m_currentState.A = sf::Joystick::isButtonPressed(0, 0);
	m_currentState.B = sf::Joystick::isButtonPressed(0, 1);
	m_currentState.X = sf::Joystick::isButtonPressed(0, 2);
	m_currentState.Y = sf::Joystick::isButtonPressed(0, 3);

	//bumpers, back, start and thumbstick clicks
	m_currentState.LB = sf::Joystick::isButtonPressed(0, 4);
	m_currentState.RB = sf::Joystick::isButtonPressed(0, 5);
	m_currentState.Back = sf::Joystick::isButtonPressed(0, 6);
	m_currentState.Start = sf::Joystick::isButtonPressed(0, 7);
	m_currentState.LeftThumbStickClick = sf::Joystick::isButtonPressed(0, 8);
	m_currentState.RightThumbStickClick = sf::Joystick::isButtonPressed(0, 9);

	//triggers and thumbsticks
	m_currentState.LTtrigger = (sf::Joystick::getAxisPosition(0,sf::Joystick::Axis::Z));
	m_currentState.RTtrigger = (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z));
	m_currentState.LeftThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X), (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y)));
	m_currentState.RightThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R), (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U)));

	// DPad Button Analogs
	m_currentState.DpadDown = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) < -DPAD_THRESHOLD;
	m_currentState.DpadUp = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > DPAD_THRESHOLD;
	m_currentState.DpadLeft = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < -DPAD_THRESHOLD;
	m_currentState.DpadRight = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > DPAD_THRESHOLD;

	// Right Thumb Stick Button Analogs
	m_currentState.RightThumbStickDown = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R) > THUMB_STICK_THRESHOLD;
	m_currentState.RightThumbStickUp = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R) < -THUMB_STICK_THRESHOLD;
	m_currentState.RightThumbStickLeft = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U) < -THUMB_STICK_THRESHOLD;
	m_currentState.RightThumbStickRight = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U) > THUMB_STICK_THRESHOLD;

	// Left Thumb Stick Button Analogs
	m_currentState.LeftThumbStickDown = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > THUMB_STICK_THRESHOLD;
	m_currentState.LeftThumbStickUp = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < -THUMB_STICK_THRESHOLD;
	m_currentState.LeftThumbStickLeft = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -THUMB_STICK_THRESHOLD;
	m_currentState.LeftThumbStickRight = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > THUMB_STICK_THRESHOLD;
}

/*simple method that will write out whether a controller is connected or not to the console*/ 
bool Xbox360Controller::isConnected()
{
	if (sf::Joystick::isConnected(0) == true)
	{
		std::cout << "Controller Connected";
		sf_Joystick_index = 0;
		return true;
	}
	std::cout << "No Controller Connected";
	return false;
}