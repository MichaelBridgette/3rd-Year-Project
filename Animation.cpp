#include "Animation.h"
/// <summary>
/// @mainpage Joint Project - 2D racing game.
/// @Author Dylan Murphy, Sean Regan, Micheal Bridgette, David O'Gorman
/// @Version 1.0
/// @brief A 2D racing game.
/// </summary>

Animation::Animation()
{
	playOnce = false;
}

Animation::Animation(sf::Texture * texture, sf::Vector2u imageCount, float switchTime)
{
	playOnce = false;
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
	animationFinished = false;
}

void Animation::update(int row, float dt)
{
	//animationFinished = false;
	currentImage.y = row;
	totalTime += dt;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			if (!playOnce)
			{
				currentImage.x = 0;
			}
			animationFinished = true;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

bool Animation::isAnimFinished()
{
	return animationFinished;
}

void Animation::setFinished(bool isFinish)
{
	animationFinished = isFinish;
}

void Animation::PlayAnimationOnce(bool b)
{
	playOnce = b;
}

void Animation::reset()
{
	currentImage.x = 0;
	animationFinished = false;
}
