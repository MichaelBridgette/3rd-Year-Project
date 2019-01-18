#include "Bomb.h"

Bomb::Bomb(b2World& world, float x, float y, float const scale) :
	m_world(world)
{
	BodyDef.position = b2Vec2(x / scale, y / scale);
	BodyDef.type = b2_dynamicBody;
	Body = world.CreateBody(&BodyDef);
	Body->SetFixedRotation(false);

	capsule.m_p.Set(16.f / scale, 16.f / scale);
	capsule.m_radius = 16.f / scale;

	FixtureDef.density = 0.f;
	FixtureDef.shape = &capsule;
	FixtureDef.friction = 1.f;
	FixtureDef.restitution = 0.3f;
	Body->CreateFixture(&FixtureDef);

	m_circleShape.setTexture(g_resourceManager.m_textureHolder["Bomb"]);
	m_circleShape.setPosition(Body->GetPosition().x * scale, Body->GetPosition().y * scale);
	m_circleShape.setOrigin(16, 16);

	// Debug Code
	//m_outer.setOutlineColor(sf::Color::White);
	//m_outer.setOutlineThickness(2);
	//m_outer.setFillColor(sf::Color::Blue);
	m_outer.setRadius(145);
	m_outer.setOrigin(145, 145);

	
	
	//Body->SetFixedRotation(false);
	counter = 0;
	explode = false;
	alive = true;

	m_animTexture = g_resourceManager.m_textureHolder["Boom"];
	m_animExplosion = Animation(&m_animTexture, sf::Vector2u(14, 1), 0.05f);
	m_animExplosion.PlayAnimationOnce(true);

	m_boom.setBuffer(g_resourceManager.m_soundHolder["Boom"]);
	m_boom.setVolume(g_resourceManager.m_soundResourceVolume);

	m_boom.setLoop(false);
}

void Bomb::Draw(sf::RenderWindow & window)
{
	if (alive)
	{
		window.draw(m_circleShape);
		// Debug Code
		// window.draw(m_outer);	
	}
	else if (m_animating)
	{
		window.draw(m_sprite);
	}
}

sf::Vector2f Bomb::getPos()
{
	return sf::Vector2f();
}

void Bomb::Update(sf::Time t_deltaTime)
{
	if (alive)
	{
		m_circleShape.setPosition(Body->GetPosition().x * 30 + 8, Body->GetPosition().y * 30 + 8);
		m_circleShape.setRotation(180 / b2_pi * Body->GetAngle());
		m_outer.setPosition(Body->GetPosition().x * 30, Body->GetPosition().y * 30);
		m_outer.setRotation(180 / b2_pi * Body->GetAngle());
	}
	else if (m_animating)
	{
		if (m_animExplosion.isAnimFinished())
		{
			m_animating = false;
		}
		m_animExplosion.update(0, t_deltaTime.asSeconds());
		m_sprite.setTexture(m_animTexture);
		m_sprite.setTextureRect(m_animExplosion.uvRect);
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);
		
	}

	// logic
	counter++;
	if (counter > 180 && explode == false && alive==true)
	{
		Explode(true);
		destroyBomb();
		counter = 0;
	}
}

void Bomb::applyForce(b2Vec2 force)
{
	Body->ApplyForceToCenter(force,true);
}

sf::CircleShape & Bomb::getOuter()
{
	return m_outer;
}

void Bomb::Explode(bool b)
{
	m_boom.play();
	explode = b;
}

bool Bomb::isExplode()
{
	return explode;
}

b2Body * Bomb::getBody()
{
	return Body;
}

void Bomb::destroyBomb()
{
	if (alive)
	{
		m_sprite.setPosition(Body->GetPosition().x * 30, Body->GetPosition().y * 30);
		m_sprite.setScale(3.f, 3.f);
		m_world.DestroyBody(Body);
		alive = false;
		m_animating = true;

	}
}