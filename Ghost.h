#ifndef GHOST_H
#define GHOST_H

#include <SFML\Graphics.hpp> // SFML
#include <SFML\Audio.hpp> // SFML
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
/// Class representing the ghosts in the game which can float through geometry and attack the player
/// </summary>
class Ghost
{
public:
	Ghost(sf::Vector2f positionIn, float speedIn, float radiusIn, float activationDistance); // Constructor
	~Ghost(); // Destructor
	void update(sf::Time t_deltaTime, Player & player); // Update method
	void draw(sf::RenderWindow &window); // Render method
	void destroy(); // Method for killing the ghost
	sf::Sprite getSprite(); // Getter for the ghost sprite
	bool getState(); // Check if the ghost is alive or not
	void setSoundVolume(float volume); // Set the volume of the ghosts attack noise *******************************************************
private:

	// Member Variables
	sf::Vector2f m_flockPoint; // Point that the ghost will flock around when they aren't following the player
	sf::Vector2f m_position; // Current position
	sf::Vector2f m_velocity; // Current velocity
	float m_radius; // Radius of the attack point
	float m_speed; // Speed of the ghost
	float m_activationDistance; // How close the player must come before the ghost will start following them
	bool m_followingPlayer; // Boolean to show when the ghost is following the player
	bool m_alive; // Boolean to tell whether the ghost is alive or not (ironic)
	int m_followThreshold = 15; // If the ghost is close enough they will not follow the player any more
	int m_hitRange = 40; // How close the ghost has to be before they hit the player

	// Graphics Members
	Animation m_animeMove;
	sf::Texture m_textureMove;
	sf::Texture m_baseTexture;
	sf::Sprite m_baseSprite;

	// Particle System Members
	sf::Texture m_particleTexture;
	thor::UniversalEmitter m_emitter;
	thor::ParticleSystem m_particleSystem;
	thor::ForceAffector m_gravityAffector;
	sf::Time m_animationMS = sf::seconds(0.1f);
	sf::Time m_animStartTime;
	sf::Time m_totalTime;

	// Sound members
	sf::Sound m_die;
	sf::Sound m_attack;
};

#endif