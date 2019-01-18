#include "Enemy.h"

/// <summary>
/// Enemy Constructor Function
/// </summary>
/// <param name="world">Reference to the Box2D world</param>
/// <param name="x">Enemy's X Position</param>
/// <param name="y">Enemy's Y Position</param>
/// <param name="xMin">Leftmost Enemy Patrol Point</param>
/// <param name="xMax">Rightmost Enemy Patrol Point</param>
/// <param name="speed">Enemy's Speed</param>
/// <param name="activationDistance">This distance between the Player and Enemy when the Enemy will begin to follow the player</param>
/// <param name="scale">Box2D world scale (pixels to metres)</param>
Enemy::Enemy(b2World& world, float x, float y, float xMin, float xMax, float speed, float activationDistance, float const scale) :
	m_speed(speed),
	m_xMin(xMin / scale),
	m_xMax(xMax / scale),
	m_scale(scale),
	m_activationDistance(activationDistance),
	m_followingPlayer(false),
	m_alive(true),
	m_attacking(false),
	m_hitting(false),
	m_world(world),
	m_gravityAffector(sf::Vector2f(0, 600))
{
	// Body Code
	m_bodyDef.position = b2Vec2(x / scale, y / scale);
	m_bodyDef.type = b2_dynamicBody;
	m_body = world.CreateBody(&m_bodyDef);

	// Capsule Collider Code
	m_capsule.m_p.Set((64.f / 2) / scale, (64.f / 2) / scale);
	m_capsule.m_radius = (64.f / 2) / scale;

	// Fixture Code
	m_fixtureDef.density = 1.f;
	m_fixtureDef.shape = &m_capsule;
	m_fixtureDef.friction = 0.0f;
	m_fixtureDef.restitution = 0.0f;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);

	// Sprite Code
	m_baseSprite.setPosition(m_body->GetPosition().x * scale, m_body->GetPosition().y * scale);
	m_baseSprite.setRotation(180 / b2_pi * m_body->GetAngle());
	m_baseSprite.setOrigin(32, 30);
	m_textureMove = g_resourceManager.m_textureHolder["EnemyWalk"]; // Load the texture from the resource manager
	m_textureAttack = g_resourceManager.m_textureHolder["EnemyAttack"]; // Load the texture from the resource manager
	m_baseSprite.setTexture(m_textureMove);
	m_animeMove = Animation(&m_textureMove, sf::Vector2u(4, 1), 0.1f);
	m_animeAttack = Animation(&m_textureAttack, sf::Vector2u(3, 1), 0.1f);
	m_animeAttack.PlayAnimationOnce(true);

	// Particle System Code
	m_bloodSplatterTexture = g_resourceManager.m_textureHolder["Blood"];
	m_particleSystem.setTexture(m_bloodSplatterTexture);
	m_emitter.setEmissionRate(0);
	m_emitter.setParticleColor(sf::Color(255, 255, 255, 255));
	m_emitter.setParticleLifetime(sf::seconds(6.f));
	m_emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, -450), 100.f));
	m_emitter.setParticleScale(sf::Vector2f(1.f, 1.f));
	m_particleSystem.addEmitter(thor::refEmitter(m_emitter));
	m_particleSystem.addAffector(thor::refAffector(m_gravityAffector));

	// Sound code
	m_attack.setBuffer(g_resourceManager.m_soundHolder["Slash"]);
	m_attack.setVolume(g_resourceManager.m_soundResourceVolume);
	m_die.setBuffer(g_resourceManager.m_soundHolder["Hit"]);
	m_die.setVolume(g_resourceManager.m_soundResourceVolume);
}

/// <summary>
/// Enemy Destructor Function
/// </summary>
Enemy::~Enemy()
{
	if (m_alive)
	{
		m_world.DestroyBody(m_body); // Destroy the Box2D body if the Enemy was still alive at the time of destruction
	}
}

/// <summary>
/// Enemy Update Method
/// </summary>
/// <param name="t_deltaTime">Time passed since the last update</param>
/// <param name="player">A reference to the Player</param>
void Enemy::update(sf::Time t_deltaTime, Player & player)
{
	if (m_alive) // Enemy is alive
	{ 
		// Logic for player tracking
		sf::Vector2f playerPos = player.getPos(); // Get the player's position
		float x = m_body->GetPosition().x * m_scale; // Get the Enemy's x position
		float y = m_body->GetPosition().y * m_scale; // Get the Enemy's y position
		float distanceToPlayer = sqrt((playerPos.x - x) * (playerPos.x - x) + (playerPos.y - y) * (playerPos.y - y)); // Get the distance between the enemy and the player
		float absY = abs(playerPos.y - y); // Get the absolute distance on solely the Y axis
		float xToPlayer = playerPos.x - x; // Get the diffeence between the Player's X position and the Enemy's X Position
		if (abs(xToPlayer) < m_activationDistance) // Check if the enemy is close enough to the player
		{
			if ((m_speed / abs(m_speed)) == (xToPlayer / abs(xToPlayer)) && !m_hitting) // Check if the Enemy is facing the player and not currently attacking
			{
				m_followingPlayer = true; // Set the Enemy to follow the player
				if (distanceToPlayer < 80 && !m_attacking) // Attack the player if the are close enough and the enemy is not already attacking
				{
					m_attacking = true;
					m_hitRegisterTime = m_totalTime;
				}
			}
		}
		else
		{
			// If the player is to far away we don't follow and don't attack
			m_followingPlayer = false;
			m_attacking = false;
		}

		if (m_followingPlayer)
		{
			if (((xToPlayer > m_followThreshold && m_speed <= 0) || (xToPlayer < -m_followThreshold && m_speed > 0)) && absY < 100) // If statement makes sure that the enemy is chasing the player (absY will make sure that the enemy will only follow the player if their heights are similar enough)
			{
				m_speed = -m_speed; // If the Enemy is following the player and isn't facing the right way, force them o turn around
			}
		}
		else if (m_hitting)
		{
			m_speed = 0; // Make sure the Enemy cannot move if they are currently hitting
		}
		else if (m_body->GetLinearVelocity().x == 0 ||  // Otherwise we make sure that the enemy is patrolling correctly
			(m_body->GetPosition().x < m_xMin && m_speed < 0) ||  // We check speed for OR no. 2 and 3 as we don't want the enemy to get stuck into a loop of changing directions
			(m_body->GetPosition().x > m_xMax && m_speed > 0))
		{
			m_speed = -m_speed;
		}
		m_body->SetLinearVelocity(b2Vec2(m_speed, m_body->GetLinearVelocity().y));

		if (m_attacking && m_totalTime.asSeconds() - m_hitRegisterTime.asSeconds() >= m_hitDelay.asSeconds()) // Check whether or not the Enemy must be attacking (delay not needed but can make the game easier)
		{
			m_attacking = false;
			m_hitting = true; // Set hitting to be true
			m_attack.play(); // Setup and play the attack animation
			m_baseSprite.setTexture(m_textureAttack);
			m_animeAttack.reset();
			m_animeAttack.update(0, t_deltaTime.asSeconds());
			m_baseSprite.setTextureRect(m_animeAttack.uvRect);
			
		}

		// Deal with display (sprites)
		if (m_speed < 0 && m_baseSprite.getScale().x != -1) // We must check direction via speed
		{
			m_baseSprite.setScale(-1, 1); // Invert the sprirte to make him go left
		}
		else if (m_speed > 0 && m_baseSprite.getScale().x != 1)
		{
			m_baseSprite.setScale(1, 1); // Otherwise he must go right
		}
		
		if (m_hitting)
		{
			m_baseSprite.setTextureRect(m_animeAttack.uvRect);
			m_animeAttack.update(0, t_deltaTime.asSeconds()); // Update the animation
			
			if (m_animeAttack.isAnimFinished()) // Check when the attack animation has finished
			{
				// Reset attack variables
				m_hitting = false;
				m_animeMove.reset();
				m_baseSprite.setTexture(m_textureMove);
				m_baseSprite.setTextureRect(m_animeMove.uvRect);
				m_animeAttack.reset();
				if (distanceToPlayer < 80)
				{
					player.loseHealth(); // If the player was close enough take away some health
				}
			}
		}
		else
		{
			m_animeMove.update(0, t_deltaTime.asSeconds()); // Update the animation
			m_baseSprite.setTextureRect(m_animeMove.uvRect);
		}
		
		m_baseSprite.setPosition(m_body->GetPosition().x * 30.f + 32, m_body->GetPosition().y * 30.f + 32);
		m_baseSprite.setRotation(180 / b2_pi * m_body->GetAngle());
		m_animStartTime = m_totalTime;
	}
	else // Enemy is Dead
	{
		// Update their particle system
		m_emitter.setParticlePosition(m_baseSprite.getPosition());
		m_particleSystem.update(t_deltaTime);
		if (m_animStartTime + m_animationMS <= m_totalTime)
		{
			m_emitter.setEmissionRate(0.f); // Stop particles from being emitted after a short period of time
		}
	}
	m_totalTime += t_deltaTime; // Keep track of the time passed thus far
}

/// <summary>
/// Render method for the Enemy
/// </summary>
/// <param name="window">Window to which the enemy is to be drawn</param>
void Enemy::draw(sf::RenderWindow &window)
{
	if (m_alive)
	{
		window.draw(m_baseSprite); // Draw the Enemy if they are alive
	}
	else
	{
		window.draw(m_particleSystem); // Otherwise draw heir particle effect
	}
}

/// <summary>
/// Method to allow the Enemy to be destroyed
/// </summary>
void Enemy::destroy()
{
	if (m_alive) // We don't want to kill the Enemy if they are already dead
	{
		// Set up the particle effects
		m_emitter.setParticlePosition(m_baseSprite.getPosition()); 
		m_emitter.setEmissionRate(90);
		m_world.DestroyBody(m_body); // Destroy the body to prevent odd collisions
		m_alive = false;
		m_die.play(); // Play the Enemy's death sound
	}
}

/// <summary>
/// Getter method returning the Enemy's sprite
/// </summary>
/// <returns>m_baseSprite : The Enemy's sprite</returns>
sf::Sprite Enemy::getSprite()
{
	return m_baseSprite;
}

/// <summary>
/// Getter method used to check whether or not the Enemy is alive
/// </summary>
/// <returns>m)alive : Boolean representing whether or not the Enemy is alive</returns>
bool Enemy::getState()
{
	return m_alive;
}

/// <summary>
/// Function used to setthe volume of the enemy's sounds
/// </summary>
/// <param name="volume">Volume to be used</param>
void Enemy::setSoundVolume(float volume)
{
	// Set Volumes
	m_attack.setVolume(volume);
	m_die.setVolume(volume);
}
