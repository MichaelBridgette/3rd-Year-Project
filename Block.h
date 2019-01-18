#ifndef BLOCK_H
#define BLOCK_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

#include "ResourceManager.h"

class Block {

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	b2BodyDef m_bodyDef;
	b2Body * m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2World & m_world;
	bool m_alive;
	bool concrete;
	std::string fileName;

	

public:
	Block(b2World & world, float x, float y, int txtrX, int txtrY, bool concreteIn, float const SCALE);
	~Block();
	void Draw(sf::RenderWindow &window);
	sf::Vector2f getPos();
	void destroyBody();
	sf::Sprite& getSprite();
	void setConcrete(bool b);
	bool isConcrete();
	std::string getFileName();


	float x;
	float y;
	std::string id;
	float blocksX = 16;
	float blocksY = 9;

};

#endif // !BLOCK_H