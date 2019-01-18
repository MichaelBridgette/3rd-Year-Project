#ifndef MOVEABLEBLOCK_H
#define MOVEABLEBLOCK_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

class MoveableBlock {

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
	MoveableBlock(b2World & world, float x, float y, float const SCALE);
	~MoveableBlock();
	void Draw(sf::RenderWindow &window);
	void Update();
	sf::Vector2f getPos();
	void destroyBody();
	sf::Sprite& getSprite();
	void setConcrete(bool b);
	bool isConcrete();
	std::string getFileName();
};

#endif // !MOVEABLEBLOCK_H
