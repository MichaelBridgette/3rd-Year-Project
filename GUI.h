#pragma once
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>

#include"Button.h"
#include"RadioButton.h"
#include"Slider.h"
#include"Label.h"
#include"Widget.h"
#include<SFML\Graphics.hpp>
#include"XBOX360CONTROLLER.h"
#include<SFML\Audio.hpp>
#include"CheckBox.h"
#include"ResourceManager.h"

//will contain all ui elements
class GUI
{
public:
	GUI();
	~GUI();
	void addLabel(Label *label); //add label
	void addButton(Button *button); //add button
	void addSlider(Slider *slider); //add slider
	void addRadioButton(RadioButton *radioButton);// add radioButton
	void addCheckBox(CheckBox *checkBox); //add checkbox
	void addWidget(Widget *widget); // add widget(can be used instead of all of the above adds)
	void update(int &index, int maxItems); //update loop
	void draw(sf::RenderWindow &window); //draw loop
	void moveUp(int &index); // move up to the next element
	void moveDown(int &index, int maxItems); //move down

	void moveUp2(int &index); //alternative
	void moveDown2(int &index, int maxItems); //alternative
	void activate(int &index); //activate function of current element
	void increaseSliderValue(int &index); //increase the value of a slider
	void decreaseSliderValue(int &index); //decrease
	void verticalControls(int &index, int maxItems); //controls designed to be used dpad vertically only
	void horizontalControls(int &index, int maxItems); //left and right only
	void vertAndHorControls(int &index, int maxItems); //mixture
	void removeAllElements(); //clear the containers
	
	
	bool vertical; //when true use vert controls
	bool horizontal; //use horizontal
	bool both; //use mixture
	static bool useAnim;
	static sf::Clock m_timeBetweenClicks;

	sf::SoundBuffer m_buffer;
	sf::Sound m_guiSound; //gui soundeffect that plays when moving through elements

private:
	std::vector<Widget *> m_elements; // container to hold all widgets
	std::vector<Label *>m_labels; //holds all labels, labels can be also stored in m_elements
	Xbox360Controller m_xbox; //xbox controller
	sf::Clock m_timer; //timer
	double timeElapsed;
	bool animating; //when element is undergoeing an animation 
	bool move = false;


	int counter;
	bool startCount = false;

};
