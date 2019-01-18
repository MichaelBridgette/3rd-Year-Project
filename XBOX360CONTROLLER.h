#ifndef  XBOX360CONTROLLER
#define XBOX360CONTROLLER

#include <SFML\Graphics.hpp>
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>

struct GamePadState
{
	bool A;  //a bool that will be true if A is pressed
	bool B;  //a bool that will be true if B is pressed            
	bool X;  //a bool that will be true if X is pressed
	bool Y;  //a bool that will be true if Y is pressed
	bool LB; //a bool that will be true if LB is pressed
	bool RB; //a bool that will be true if RB is pressed
	bool LeftThumbStickClick; //a bool that will be true if left thumbstick is pressed
	bool RightThumbStickClick; //a bool that will be true if right thumbstick is pressed
	bool DpadUp; //a bool that will be true if dpad up is pressed
	bool DpadDown; //a bool that will be true if dpad down is pressed
	bool DpadLeft; //a bool that will be true if dpad left is pressed
	bool DpadRight; //a bool that will be true if dpad right is pressed
	bool Start; //a bool that will be true if start is pressed
	bool Back; //a bool that will be true if back is pressed
	float RTtrigger; //this float value will represent the degree value for the right trigger
	float LTtrigger; //this float value will represent the degree value for the left trigger
	sf::Vector2f RightThumbStick; //a vector that will represent the x and y coords for the right thumbstick
	sf::Vector2f LeftThumbStick; //a vector that will represent the x and y coords for the left thumbstick

	// Team Right Thumb Stick
	bool RightThumbStickLeft;
	bool RightThumbStickRight;
	bool RightThumbStickUp;
	bool RightThumbStickDown;

	// Team Left Thumb Stick
	bool LeftThumbStickLeft;
	bool LeftThumbStickRight;
	bool LeftThumbStickUp;
	bool LeftThumbStickDown;
};

class Xbox360Controller
{
private:
	const int DPAD_THRESHOLD = 10; //this const will be used to help indicate which dpad button is being pressed 
	const int THUMB_STICK_THRESHOLD = 50; // This is mainly used for UI to alow the joysticks to be used like buttons while naviagting the GUI

public:
	int sf_Joystick_index; //a number that represents our joysticks number
	GamePadState m_currentState; //will use this to set the appropriate bools to true when the right button is pressed
	GamePadState m_previousState; //will be set to what current state holds on every update iteration
	
	Xbox360Controller(); //default constructor
	~Xbox360Controller();// deconstructor 
	void Xbox360Controller::update(); //update function where I check for joystick input
	bool isConnected(); //simple check to see if controller is connected 
};

#endif // ! XBOX360CONTROLLER