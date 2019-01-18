#include "Pickup.h"

int Pickup::random  = time(NULL);

Pickup::Pickup(bool score, bool health, bool bomb, sf::Vector2f pos)
{
	isScore = score;
	isHealth = health;
	isBomb = bomb;

	isAlive = true;
	count = 0;
	particleCount = 0;
	m_position = pos;
	srand(random);
	if (isScore)
	{
		
		random = rand() % 10 + 1;
		if (!m_texture.loadFromFile("treasure" + std::to_string(random)+".png"))
		{
			std::cout << "failed to load treasure" << std::endl;
		}
		
	}
	else if (isBomb)
	{
		if (!m_texture.loadFromFile("bomb2.png"))
		{
			std::cout << "failed to load bomb pickup" << std::endl;
		}
	}
	else if (isHealth)
	{
		if (!m_texture.loadFromFile("potion.png"))
		{
			std::cout << "failed to load health pickup" << std::endl;
		}
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);


	if (!Particle.loadFromFile("particle.png"))
	{
		std::cout << "failed to load particle texture" << std::endl;
	}
	particles.setTexture(Particle);

	emitter.setEmissionRate(60);
	emitter.setParticleLifetime(sf::seconds(0.2));
	emitter.setParticlePosition(m_sprite.getPosition());
	emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(-100, -400), 180.f));
	emitter.setParticleColor(sf::Color(255, 225, 0));
	emitter.setParticleScale(sf::Vector2f(1, 1));
	particles.addEmitter(thor::refEmitter(emitter));
	
	m_sound.setBuffer(g_resourceManager.m_soundHolder["Pickup"]);
	m_sound.setVolume(g_resourceManager.m_soundResourceVolume);
}

Pickup::~Pickup()
{
}

void Pickup::draw(sf::RenderWindow & window)
{
	
	if (isAlive)
	{
		window.draw(m_sprite);
	}
	window.draw(particles);
}

void Pickup::update(sf::Time t_deltaTime)
{
	emitter.setParticlePosition(m_sprite.getPosition()+ sf::Vector2f(25,20));
	particles.update(t_deltaTime);

	if (isAlive)
	{
		emitter.setEmissionRate(0);
	}
	else
	{
		particleCount++;
		emitter.setEmissionRate(500);
	}

	if (particleCount > 15)
	{
		emitter.setEmissionRate(0);
	}
	count++;

	if (count < 60)
	{
		m_position.y += 0.2f;
	}
	else if (count > 60 && count<120)
	{
		m_position.y -= 0.2f;
	}
	if (count > 120)
	{
		count = 0;
	}
	m_sprite.setPosition(m_position);
}

void Pickup::checkCollision(sf::Sprite sprite)
{
	if (m_sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) && isAlive==true)
	{
		isAlive = false;
		m_sound.play();
	}
}

bool Pickup::isABomb()
{
	return isBomb;
}

bool Pickup::isAHealth()
{
	return isHealth;
}

bool Pickup::isAScore()
{
	return isScore;
}

bool Pickup::isColliding(sf::Sprite sprite)
{
	if (isAlive && m_sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

void Pickup::setMusicVolume(float volume)
{
	m_sound.setVolume(volume);
}
