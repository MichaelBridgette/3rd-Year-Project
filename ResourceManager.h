#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <Thor\Resources.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

class ResourceManager
{
public:
	void loadAssets();
	thor::ResourceHolder<sf::Texture, std::string> m_textureHolder;
	thor::ResourceHolder<sf::Font, std::string> m_fontHolder;
	thor::ResourceHolder<sf::SoundBuffer, std::string> m_soundHolder;

	float m_soundResourceVolume = 20;
};

extern ResourceManager g_resourceManager;

#endif
