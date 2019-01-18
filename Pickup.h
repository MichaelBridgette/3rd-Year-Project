#pragma once
#include <SFML\Graphics.hpp>
#include <stdlib.h> 
#include<string>
#include <Thor\Resources.hpp>
#include <Thor\Particles.hpp>
#include <Thor\Config.hpp>
#include <Thor\Graphics.hpp>
#include <Thor\Math.hpp>
#include<iostream>
#include<SFML\Audio.hpp>
#include "ResourceManager.h"

class Pickup {
public:
	Pickup(bool score, bool health, bool bomb, sf::Vector2f pos);
	~Pickup();
	void draw(sf::RenderWindow &window);
	void update(sf::Time t_deltaTime);

	void checkCollision(sf::Sprite sprite);
	bool isABomb();
	bool isAHealth();
	bool isAScore();

	bool isColliding(sf::Sprite sprite);

	void setMusicVolume(float volume);

private:
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool isScore;
	bool isHealth;
	bool isBomb;

	bool isAlive;
	int count;
	int particleCount;

	sf::Texture Particle;
	thor::ParticleSystem particles;
	thor::UniversalEmitter emitter;

	static int random;
	sf::Sound m_sound;
};