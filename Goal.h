#ifndef GOAL_H
#define GOAL_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

#include "ResourceManager.h"

class Goal {

public:
	Goal(std::string filename, float x, float y);
	~Goal();
	
	void Draw(sf::RenderWindow &window);
	sf::Vector2f getPos();
	sf::Sprite& getSprite();
	std::string getFileName();
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool m_alive;
	std::string fileName;
};

#endif // !GOAL_H