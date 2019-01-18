#ifndef ENEMY_H
#define ENEMY_H

#include <SFML\Graphics.hpp> // SFML
#include <SFML\Audio.hpp> // SFML
#include <Box2D\Box2D.h> //Box2D
#include <Thor\Resources.hpp> // THOR
#include <Thor\Particles.hpp> // THOR
#include <Thor\Config.hpp> // THOR
#include <Thor\Graphics.hpp> // THOR
#include <Thor\Math.hpp> // THOR
#include <iostream> // STD

#include "Animation.h"
#include "ResourceManager.h"
#include "Player.h"

/// <summary>
/// Enemy class representing the patrolling enemy with a Box2D body for collisions
/// </summary>
class Enemy {
public:
	Enemy(b2World& world, float x, float y, float xMin, float xMax, float speed, float activationDistance, float const scale); // Constructor function
	~Enemy(); // Destructor function
	void update(sf::Time t_deltaTime, Player & player); // Update function
	void draw(sf::RenderWindow &window); // Render function
	void destroy(); // Function allowing the enemy to be killed
	sf::Sprite getSprite(); // Getter function for the enemy sprite
	bool getState(); // Check if the enemy is alie or not
	void setSoundVolume(float volume); // *******************************************************************************************************************
private:

	// Member Variables
	float m_speed;
	float m_xMin;
	float m_xMax;
	float m_scale;
	float m_activationDistance;
	bool m_followingPlayer;
	bool m_alive;
	bool m_attacking;
	bool m_hitting;
	int m_followThreshold = 15;

	// Box2D Members
	b2World & m_world;
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2CircleShape m_capsule;
	b2FixtureDef m_fixtureDef;

	// Graphics Members
	Animation m_animeMove;
	Animation m_animeAttack;
	sf::Texture m_textureMove;
	sf::Texture m_textureAttack;
	sf::Sprite m_baseSprite;

	// Particle System Members
	sf::Texture m_bloodSplatterTexture;
	thor::UniversalEmitter m_emitter;
	thor::ParticleSystem m_particleSystem;
	thor::ForceAffector m_gravityAffector;
	sf::Time m_animationMS = sf::seconds(0.1f);
	sf::Time m_hitDelay = sf::seconds(0.0f);
	sf::Time m_animStartTime;
	sf::Time m_hitRegisterTime;
	sf::Time m_totalTime;

	// Sounds
	sf::Sound m_attack;
	sf::Sound m_die;
};

#endif