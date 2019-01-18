#include "Block.h"

Block::Block(b2World & world, float x, float y, int txtrX, int txtrY, bool concreteIn, float const SCALE):
	m_world(world)
{
	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_staticBody;
	m_body = world.CreateBody(&m_bodyDef);
	m_shape.SetAsBox((64.f / 2) / SCALE, (64.f / 2) / SCALE);
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.1f;
	m_fixtureDef.restitution = 0.0f;
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);
	m_sprite.setTexture(g_resourceManager.m_textureHolder["Block"]);
	float w = m_sprite.getGlobalBounds().width;
	float h = m_sprite.getGlobalBounds().height;
	m_sprite.setTextureRect(sf::IntRect(w * (txtrX / blocksX), h * (txtrY / blocksY), 64, 64));
	m_sprite.setOrigin(64 / 2, 64 / 2);
	m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
	m_alive = true;
	concrete = concreteIn;
}

Block::~Block() 
{
	if (m_alive)
	{
		m_world.DestroyBody(m_body);
	}
}

void Block::Draw(sf::RenderWindow &window)
{
	if(m_alive)
	window.draw(m_sprite);
}

sf::Vector2f Block::getPos()
{
	return m_sprite.getPosition();
}

void Block::destroyBody()
{
	if (m_alive)
	{
		m_world.DestroyBody(m_body);
	}
	m_alive = false;
}

sf::Sprite & Block::getSprite()
{
	return m_sprite;
}

void Block::setConcrete(bool b)
{
	concrete = true;
}

bool Block::isConcrete()
{
	return concrete;
}

std::string Block::getFileName()
{
	return fileName;
}