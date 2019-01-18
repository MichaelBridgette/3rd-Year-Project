#include "Goal.h"

Goal::Goal(std::string filename, float x, float y)
{
	/*fileName = filename;
	if (!m_texture.loadFromFile(filename))
	{
		std::cout << "Error Loading Block Texture!" << std::endl;
	}*/
	m_texture = g_resourceManager.m_textureHolder["Goal"];
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(256/2 , 256-32);
	m_sprite.setPosition(x, y);
	m_alive = true;
}

Goal::~Goal() {}

void Goal::Draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

sf::Vector2f Goal::getPos()
{
	return m_sprite.getPosition();
}

sf::Sprite & Goal::getSprite()
{
	// TODO: insert return statement here
	return m_sprite;
}

std::string Goal::getFileName()
{
	return fileName;
}
