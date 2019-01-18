#include "Ghost.h"

/// <summary>
/// Constructor function for the ghosts
/// </summary>
/// <param name="positionIn">The position of the ghost</param>
/// <param name="speedIn">The speed of the ghost</param>
/// <param name="radiusIn">How close the ghost should stay to its starting position</param>
/// <param name="activationDistance">How close the player has to come before the ghost follows them</param>
Ghost::Ghost(sf::Vector2f positionIn, float speedIn, float radiusIn, float activationDistance) :
	m_flockPoint(positionIn),
	m_position(positionIn),
	m_radius(radiusIn),
	m_speed(speedIn),
	m_activationDistance(activationDistance),
	m_alive(true),
	m_gravityAffector(sf::Vector2f(0, 400))
{
	// Sprites and animation
	m_baseSprite.setPosition(m_position);
	m_baseSprite.setOrigin(32, 30);
	m_textureMove = g_resourceManager.m_textureHolder["Ghost"]; // Load the texture from the resource manager
	m_baseSprite.setTexture(m_textureMove);
	m_animeMove = Animation(&m_textureMove, sf::Vector2u(10, 1), 0.1f);

	// Particle System
	m_particleTexture = g_resourceManager.m_textureHolder["Ectoplasm"];
	m_particleSystem.setTexture(m_particleTexture);
	m_emitter.setEmissionRate(0);
	m_emitter.setParticleColor(sf::Color(255, 255, 255, 255));
	m_emitter.setParticleLifetime(sf::seconds(6.f));
	m_emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, -450), 100.f));
	m_emitter.setParticleScale(sf::Vector2f(1.f, 1.f));
	m_particleSystem.addEmitter(thor::refEmitter(m_emitter));
	m_particleSystem.addAffector(thor::refAffector(m_gravityAffector));

	// Sounds
	m_die.setBuffer(g_resourceManager.m_soundHolder["Hit"]);
	m_die.setVolume(g_resourceManager.m_soundResourceVolume);
	m_attack.setBuffer(g_resourceManager.m_soundHolder["Ghost"]);
	m_attack.setVolume(g_resourceManager.m_soundResourceVolume);
}

/// <summary>
/// Ghost destructor function
/// </summary>
Ghost::~Ghost() {}

/// <summary>
/// Update method for the ghost
/// </summary>
/// <param name="t_deltaTime">Time since the last update</param>
/// <param name="player">A reference to the player so the ghost can follow and damage them</param>
void Ghost::update(sf::Time t_deltaTime, Player & player)
{
	sf::Vector2f playerPos = player.getPos(); // Get the player's position
	if (m_alive) // Ghost alive
	{
		float playerDistance = abs(m_position.x - playerPos.x) + abs(m_position.y - playerPos.y); // Distance to the player aproximation
		float staticPointDistance = abs(m_position.x - m_flockPoint.x) + abs(m_position.y - m_flockPoint.y); // Distance to the gost's static point approximation
		sf::Vector2f newDirection = m_velocity;

		if (playerDistance < m_hitRange) // Check if the ghost is close enoughto hurt the player
		{
			m_attack.play(); // Play the attack sound
			player.loseHealth();// Decrement the player's health
		}

		if (playerDistance < m_activationDistance) // Check if the player is close enought to follow
		{
			newDirection = playerDistance > m_followThreshold ? (playerPos - m_position) / playerDistance : sf::Vector2f(0, 0);// This will always produce a normal vector heading for between the player and the ghost
			newDirection *= m_speed;
		}

		else if (staticPointDistance > m_radius) // If the ghost is not following the player we keep them close to their starting point
		{
			if (m_flockPoint != m_position)
			{
				newDirection = (m_flockPoint - m_position) / staticPointDistance;
			}
			newDirection *= m_speed;
		}

		// Move the ghost
		m_velocity = newDirection;
		m_position += newDirection;

		// Sprite Work
		if (newDirection.x > 0)
		{
			m_baseSprite.setScale(1, 1);
		}
		else
		{
			m_baseSprite.setScale(-1, 1);
		}
		m_animeMove.update(0, t_deltaTime.asSeconds());
		m_baseSprite.setTextureRect(m_animeMove.uvRect);
		m_baseSprite.setPosition(m_position);
		
	}
	else // Ghost dead
	{
		m_emitter.setParticlePosition(m_baseSprite.getPosition()); // If the ghost is dead then we only need to update their particle system
		m_particleSystem.update(t_deltaTime);
		if (m_animationMS + m_animStartTime >= m_totalTime)
		{
			m_emitter.setEmissionRate(0); // Stop the particle system after a short time
		}
	}
	m_totalTime += t_deltaTime;
}

/// <summary>
/// Render method for the ghost class
/// </summary>
/// <param name="window">Window used to draw the ghost or its particle effect</param>
void Ghost::draw(sf::RenderWindow &window)
{
	if (m_alive)
	{
		window.draw(m_baseSprite); // Draw the ghost itself if it is alive
	}
	else
	{
		window.draw(m_particleSystem); // Otherwise draw its particle effect
	}
}

/// <summary>
/// Mtehod allowsthe ghost to be killed
/// </summary>
void Ghost::destroy()
{
	if (m_alive) // We don't want to kll the ghost of they are already dead
	{
		m_alive = false; // Set alive to be false
		m_emitter.setParticlePosition(m_baseSprite.getPosition()); // Setup the particle effects
		m_emitter.setEmissionRate(900);
		m_animStartTime = m_totalTime;
		m_die.play();
	}
}

/// <summary>
/// Getter method returns the ghost's sprite
/// </summary>
/// <returns>m_baseSprite : The ghost's sprite</returns>
sf::Sprite Ghost::getSprite()
{
	return m_baseSprite;
}

/// <summary>
/// Method returns the current state of the ghost (whether they are alive or dead)
/// </summary>
/// <returns>m_alive : The state ofthe ghost - see header</returns>
bool Ghost::getState()
{
	return m_alive;
}

/// <summary>
/// Method used to set the volume of the gost's sounds
/// </summary>
/// <param name="volume">The volume to be used</param>
void Ghost::setSoundVolume(float volume) // *****************************************************************************************************
{
	m_die.setVolume(volume);
	m_attack.setVolume(volume);
}
