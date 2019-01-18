#include "MoveableBlock.h"

MoveableBlock::MoveableBlock(b2World & world, float x, float y, float const SCALE):
	m_world(world)
{
	if (!m_texture.loadFromFile("P.png"))
	{
		std::cout << "Error Loading Block Texture!" << std::endl;
	}
	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_dynamicBody;
	m_body = world.CreateBody(&m_bodyDef);
	m_shape.SetAsBox((60.f / 2) / SCALE, (63.f / 2) / SCALE);
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.5f;
	m_fixtureDef.restitution = 0.0f;
	
	//float32 m = 20;
	//mass->mass = &m;

	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(60 / 2, 64 / 2);
	m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
	m_alive = true;
	concrete = false;

}

MoveableBlock::~MoveableBlock()
{
	if (m_alive)
	{
		m_world.DestroyBody(m_body);
	}
}

void MoveableBlock::Draw(sf::RenderWindow & window)
{
	if (m_alive)
	window.draw(m_sprite);
}

void MoveableBlock::Update()
{
	m_sprite.setPosition(m_body->GetPosition().x * 30.f , m_body->GetPosition().y * 30.f);
	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
}

sf::Vector2f MoveableBlock::getPos()
{
	return m_sprite.getPosition();
}

void MoveableBlock::destroyBody()
{
	if (m_alive)
	{
		//std::cout << "Body ded" << std::endl;
		m_world.DestroyBody(m_body);
	}
	m_alive = false;
}

sf::Sprite & MoveableBlock::getSprite()
{
	return m_sprite;
}

void MoveableBlock::setConcrete(bool b)
{
	concrete = true;
}

bool MoveableBlock::isConcrete()
{
	return concrete;
}

std::string MoveableBlock::getFileName()
{
	return fileName;
}
