#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <Box2D\Box2D.h>

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <Thor\Resources.hpp>
#include <Thor\Particles.hpp>
#include <Thor\Config.hpp>
#include <Thor\Graphics.hpp>
#include <Thor\Math.hpp>

#include "ResourceManager.h"
#include "XBOX360CONTROLLER.h"
#include "Animation.h"
#include "Bomb.h"
#include "Hud.h"

enum Direction
{
	West,
	East
};

class Player {
public:
	Player(b2World& world, float x, float y, float const scale, HUD *hud); // Constructor
	void Draw(sf::RenderWindow &window); // Player render function
	sf::Vector2f getPos();
	void Update(sf::Time t_deltaTime);
	void PlayDeathAnimation(sf::Time t_deltaTime);
	void PlayAttackAnimation(sf::Time t_deltaTime);
	void PlayWalkAnimation(sf::Time t_deltaTime);
	void UpdatePlayerDirection();
	void ThrowBomb();
	bool isPlayerAttacking();
	sf::RectangleShape getHitBox();
	std::vector<Bomb> & getBombs();
	sf::Sprite getSprite();
	void playerReset(float x, float y);
	Xbox360Controller m_xbox; //xbox controller
	bool isPlayerDead();

	void loseHealth();
	void gainHealth();

	void increaseScore();
	void increaseBombs();

	void silence(); // Stop the player sounds

	void setSoundVolume(float volume);
private:
	// Rendering SFML members
	sf::Texture m_textureIdle;
	sf::Texture m_textureMove;
	sf::Texture m_textureDie;
	sf::Texture m_textureAttack;
	bool die;
	int health;
	bool playerAlive;
	bool isAttacking;

	sf::Sprite m_sprite;

	// Box2D members
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2CircleShape m_capsule;
	b2FixtureDef m_fixtureDef;

	// Sprite Sheet stuuf (temp removed)
	sf::Vector2f tempScale;
	Animation m_animeMove;
	Animation m_animeDie;
	Animation m_animeAttack;

	Direction m_direction;

	sf::SoundBuffer m_buffer;
	sf::Sound m_walk;

	sf::SoundBuffer m_buffer2;
	sf::Sound m_slash;

	bool isWalking;
	bool loop;
	bool isJumping;

	std::vector<Bomb> m_bombs;
	b2World & m_world;
	bool m_throwBomb;

	float m_lastVerticalVelocity = 0;


	//particles
	//thor::ParticleSystem system;
	sf::Texture m_snowParticle;
	thor::ParticleSystem particles;
	//thor::Distribution dist;
	thor::UniversalEmitter emitter;


	//combat stuff
	sf::RectangleShape m_hitbox;
	sf::Vector2f m_hitboxOffset;
	sf::Vector2f m_tempOffset;

	HUD * m_hud;

	int bombCount;

	sf::SoundBuffer m_jumpBuffer;
	sf::Sound m_jump;
};

#endif