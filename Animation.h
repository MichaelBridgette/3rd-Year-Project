#pragma once
#include<SFML\Graphics.hpp>
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>

class Animation {

public:
	Animation();
	Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
	void update(int row, float dt);
	bool isAnimFinished();
	void setFinished(bool isFinish);
	sf::IntRect uvRect;
	void PlayAnimationOnce(bool b);
	void reset();
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
	bool animationFinished;
	bool playOnce;

};
