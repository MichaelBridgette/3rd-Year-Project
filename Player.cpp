#include "Player.h"

Player::Player(b2World & world, float x, float y, float const scale, HUD *hud) :
	m_world(world),
	m_hud(hud)
{
	m_buffer = g_resourceManager.m_soundHolder["Walk"];
	

	m_textureMove = g_resourceManager.m_textureHolder["PlayerMove"];
	m_textureDie = g_resourceManager.m_textureHolder["PlayerDie"];
	m_textureAttack = g_resourceManager.m_textureHolder["PlayerAttack"];

	m_bodyDef.position = b2Vec2(x / scale, y / scale);
	m_bodyDef.type = b2_dynamicBody;
	m_body = world.CreateBody(&m_bodyDef);

	m_capsule.m_p.Set((64.f / 2) / scale, (64.f / 2) / scale);
	m_capsule.m_radius = (64.f / 2) / scale;

	m_fixtureDef.density = 1.f;
	m_fixtureDef.shape = &m_capsule;
	m_fixtureDef.friction = 0.0f;
	m_fixtureDef.restitution = 0.0f;

	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);
	m_sprite.setPosition(m_body->GetPosition().x * scale, m_body->GetPosition().y * scale);
	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
	m_sprite.setOrigin(32, 30);
	m_sprite.setTexture(m_textureMove);

	m_animeMove = Animation(&m_textureMove, sf::Vector2u(4, 1), 0.1f);
	m_animeAttack = Animation(&m_textureAttack, sf::Vector2u(3, 1), 0.1f);
	m_animeDie = Animation(&m_textureDie, sf::Vector2u(5, 1), 0.1f);
	m_animeDie.PlayAnimationOnce(true);

	tempScale = m_sprite.getScale();
	m_direction = Direction::East;
	die = false;
	playerAlive = true;
	isAttacking = false;
	m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 60));

	m_walk.setBuffer(m_buffer);
	m_walk.setLoop(true);
	m_walk.setVolume(g_resourceManager.m_soundResourceVolume);

	isWalking = false;
	loop = false;
	isJumping = false;

	m_throwBomb = false;

	if (!m_snowParticle.loadFromFile("ASSETS\\SnowTextures\\snowParticle.png"))
	{
		std::cout << "failed to load particle texture" << std::endl;
	}
	particles.setTexture(m_snowParticle);

	emitter.setEmissionRate(30);
	emitter.setParticleLifetime(sf::seconds(0.15));
	emitter.setParticlePosition(m_sprite.getPosition());
	emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(-50, -50), 60.f));
	emitter.setParticleColor(sf::Color::White);
	emitter.setParticleScale(sf::Vector2f(1.5, 1.5));
	particles.addEmitter(thor::refEmitter(emitter));

	//combat
	m_hitbox.setSize(sf::Vector2f(55, 45));
	m_hitbox.setFillColor(sf::Color(0, 0, 255, 75));
	m_hitboxOffset = sf::Vector2f(5, -40);
	m_tempOffset = m_hitboxOffset;
	m_hitbox.setPosition(m_sprite.getPosition() + m_hitboxOffset);

	m_hud->setHealth(3);
	m_hud->resetBools();
	m_hud->setBombNum(3);
	m_hud->resetScore();
	bombCount = 3;
	m_buffer2 = g_resourceManager.m_soundHolder["Slash"];
	m_slash.setBuffer(m_buffer2);
	m_slash.setVolume(g_resourceManager.m_soundResourceVolume);
	m_jumpBuffer= g_resourceManager.m_soundHolder["Jump"];
	m_jump.setBuffer(m_jumpBuffer);
	m_jump.setVolume(g_resourceManager.m_soundResourceVolume);
}

void Player::Draw(sf::RenderWindow & window)
{
	window.draw(particles);
	window.draw(m_sprite);
	window.draw(m_hitbox);
}

sf::Vector2f Player::getPos()
{
	return sf::Vector2f(m_body->GetPosition().x * 30.f, m_body->GetPosition().y * 30.f);
}

void Player::Update(sf::Time t_deltaTime)
{
	health = m_hud->getHealth();
	bombCount = m_hud->getBombNum();
	m_xbox.update();
	emitter.setParticlePosition(m_sprite.getPosition() + sf::Vector2f(0, 30.f));
	particles.update(t_deltaTime);
	//particles.addEmitter(emitter);
	UpdatePlayerDirection();
	m_sprite.setPosition(m_body->GetPosition().x * 30.f + 32, m_body->GetPosition().y * 30.f + 32);
	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());

	//combat
	m_hitbox.setPosition(m_sprite.getPosition() + m_hitboxOffset);


	if (isWalking == false && loop == true || isJumping == true || playerAlive == false)
	{
		m_walk.stop();
		//particles.clearParticles();
		emitter.setEmissionRate(0);
		loop = false;
	}
	else if (isWalking == true && loop == false && isJumping == false)
	{
		m_walk.play();
		emitter.setEmissionRate(30);
		loop = true;
	}

	if (playerAlive)
	{
		m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 60));
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || m_xbox.m_currentState.X) && isAttacking == false)
		{
			isAttacking = true;
			m_slash.play();
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| m_xbox.m_currentState.LeftThumbStick.x >50) && isAttacking == false)
		{
			PlayWalkAnimation(t_deltaTime);
			m_direction = Direction::East;

			m_body->SetLinearVelocity(b2Vec2(10, m_body->GetLinearVelocity().y));

			if (isJumping == false)
			{
				isWalking = true;
			}
			//emitter.setEmissionRate(30);
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || m_xbox.m_currentState.LeftThumbStick.x <-50) && isAttacking == false)
		{
			PlayWalkAnimation(t_deltaTime);
			m_direction = Direction::West;
			m_body->SetLinearVelocity(b2Vec2(-10, m_body->GetLinearVelocity().y));
			if (isJumping == false)
			{
				isWalking = true;
			}
			//emitter.setEmissionRate(30);
		}
		else
		{
			m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));
			isWalking = false;
			emitter.setEmissionRate(0);
		}

		// Jumping Code Here
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || m_xbox.m_currentState.A) && isJumping == false > 0 && isAttacking == false)
		{
			m_body->ApplyForceToCenter(b2Vec2(0, -7500), true);
			isJumping = true;
			isWalking = false;
			emitter.setEmissionRate(0);
			m_jump.play();

		}
		else if (m_body->GetLinearVelocity().y == 0 && m_lastVerticalVelocity > 0)
		{
			isJumping = false;
		}
		m_lastVerticalVelocity = m_body->GetLinearVelocity().y != 0 ? m_body->GetLinearVelocity().y : m_lastVerticalVelocity;

		if (m_animeDie.isAnimFinished() == false&& health == 0)
		{
			die = true;
		}
		if (die)
		{
			m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));
		}
		if (isJumping)
		{
			loop = true;
			m_walk.stop();
		}
		PlayDeathAnimation(t_deltaTime);
		PlayAttackAnimation(t_deltaTime);

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::B) || m_xbox.m_currentState.B && !m_xbox.m_previousState.B) & !m_throwBomb)
		{
			ThrowBomb();
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			m_throwBomb = false;
		}
		if (m_body->GetPosition().y * 30.f > 8000) // Check if the player has fallen
		{
			die = true;
		}


		//std::cout << m_body->GetLinearVelocity().x << "," << m_body->GetLinearVelocity().y << std::endl;

		if (m_body->GetLinearVelocity().y > 10)
		{
			m_walk.stop();
			emitter.setEmissionRate(0);
		}
	}
}

void Player::PlayDeathAnimation(sf::Time t_deltaTime)
{
	if (die == true)
	{
		m_sprite.setTexture(m_textureDie);
		m_sprite.setTextureRect(m_animeDie.uvRect);
		m_animeDie.update(0, t_deltaTime.asSeconds());
		if (m_animeDie.isAnimFinished() == true)
		{
			m_animeDie.setFinished(false);
			die = false;
			m_sprite.setTextureRect(sf::IntRect(64 * 4, 0, 64, 60));
			playerAlive = false;
			silence();
		}
	}
}

void Player::PlayAttackAnimation(sf::Time t_deltaTime)
{

	if (isAttacking == true)
	{
		
		m_hitbox.setFillColor(sf::Color(255, 0, 0, 75));
		m_sprite.setTexture(m_textureAttack);
		m_sprite.setTextureRect(m_animeAttack.uvRect);
		m_animeAttack.update(0, t_deltaTime.asSeconds());
		if (m_animeAttack.isAnimFinished() == true)
		{
			
			m_animeAttack.setFinished(false);
			isAttacking = false;
			m_hitbox.setFillColor(sf::Color(0, 0, 255, 75));
		}
	}
}

void Player::PlayWalkAnimation(sf::Time t_deltaTime)
{
	m_sprite.setTexture(m_textureMove);
	m_sprite.setTextureRect(m_animeMove.uvRect);
	m_animeMove.update(0, t_deltaTime.asSeconds());
}

void Player::UpdatePlayerDirection()
{
	switch (m_direction)
	{
	default:
		break;
	case Direction::West:
		m_sprite.setScale(-1, 1);
		m_hitboxOffset = sf::Vector2f(-m_tempOffset.x - 52, m_tempOffset.y);
		break;
	case Direction::East:
		m_sprite.setScale(tempScale);
		m_hitboxOffset = m_tempOffset;
		break;
	}
}

void Player::ThrowBomb()
{
	float xLaunchPos = m_sprite.getPosition().x;
	if (m_direction == Direction::East)
	{
		xLaunchPos += 30;
	}
	else
	{
		xLaunchPos -= 30;
	}
	if (bombCount > 0)
	{
		bombCount--;
		m_hud->setBombNum(bombCount);
		m_bombs.push_back(Bomb(m_world, xLaunchPos, m_sprite.getPosition().y, 30));
		std::cout << "count:" << m_bombs.size() << std::endl;

		if (m_direction == Direction::East)
		{
			m_bombs.at(m_bombs.size() - 1).applyForce(b2Vec2(1400, -1400));
		}
		else
		{
			m_bombs.at(m_bombs.size() - 1).applyForce(b2Vec2(-1400, -1400));
		}
	}
	m_throwBomb = true;
}

bool Player::isPlayerAttacking()
{
	return isAttacking;
}

sf::RectangleShape Player::getHitBox()
{
	return m_hitbox;
}

std::vector<Bomb> & Player::getBombs()
{
	return m_bombs;
}

sf::Sprite Player::getSprite()
{
	return m_sprite;
}

void Player::playerReset(float x, float y)
{
	m_world.DestroyBody(m_body);
	m_bodyDef.position = b2Vec2(x / 30, y / 30);
	m_bodyDef.type = b2_dynamicBody;
	m_body = m_world.CreateBody(&m_bodyDef);


	m_capsule.m_p.Set((64.f / 2) / 30, (64.f / 2) / 30);
	m_capsule.m_radius = (64.f / 2) / 30;

	m_fixtureDef.density = 1.f;
	m_fixtureDef.shape = &m_capsule;
	m_fixtureDef.friction = 0.0f;
	m_fixtureDef.restitution = 0.0f;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);
	m_sprite.setPosition(m_body->GetPosition().x * 30, m_body->GetPosition().y * 30);
	m_sprite.setOrigin(32, 30);
	m_sprite.setTexture(m_textureMove);
	m_bombs.clear();
	die = false;
	health = 3;
	playerAlive = true;
	m_hud->setHealth(3);
	m_hud->resetBools();
	m_hud->setBombNum(3);
	m_hud->resetScore();
	bombCount = 3;

	m_jump.setVolume(g_resourceManager.m_soundResourceVolume);
	m_slash.setVolume(g_resourceManager.m_soundResourceVolume);
	m_walk.setVolume(g_resourceManager.m_soundResourceVolume);

}

bool Player::isPlayerDead()
{
	return playerAlive;
}

void Player::loseHealth()
{
	m_hud->decreaseHealth();
}

void Player::gainHealth()
{
	m_hud->increaseHealth();
}

void Player::increaseScore()
{
	m_hud->setScore(500);
}

void Player::increaseBombs()
{
	m_hud->increaseBombs();
}

void Player::silence()
{
	m_walk.stop();
	isWalking = false;
}

void Player::setSoundVolume(float volume)
{
	m_walk.setVolume(volume);
	m_jump.setVolume(volume);
	m_slash.setVolume(volume);
}
