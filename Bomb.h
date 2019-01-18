#ifndef BOMB_H
#define BOMB_H

#include <iostream> // STD
#include <SFML\Graphics.hpp> // SFML
#include <Box2D\Box2D.h> // BOX2D

#include "Animation.h"
#include "ResourceManager.h"

/// <summary>
/// Class representing the Bombs that can be thrown by the player
/// </summary>
class Bomb
{
public:
	Bomb(b2World& world, float x, float y, float const scale); // Constructor Function
	void Update(sf::Time t_deltaTime); // Update function
	void Draw(sf::RenderWindow &window); // Render function
	
	// Functions for interacting with the object
	void applyForce(b2Vec2 force);
	void destroyBomb();
	void Explode(bool b);
	
	// Getter functions
	sf::CircleShape & getOuter();
	bool isExplode();
	b2Body * getBody();
	sf::Vector2f getPos();
	
private:
	// Box2D members
	b2World & m_world;
	b2BodyDef BodyDef;
	b2Body* Body;
	b2CircleShape capsule;
	b2FixtureDef FixtureDef;
	
	// Sprite members
	sf::Sprite m_circleShape;
	sf::Texture m_texture;
	
	// Logic members
	sf::CircleShape m_outer;
	int counter;
	bool explode;
	bool alive;

	// Animation members
	sf::Texture m_animTexture;
	sf::Texture m_bombTexture;
	sf::Sprite m_sprite;
	Animation m_animExplosion;
	bool m_animating = false;

	// Sounds members
	sf::SoundBuffer m_buffer;
	sf::Sound m_boom;
};

#endif