#include "ResourceManager.h"

ResourceManager g_resourceManager;

void ResourceManager::loadAssets()
{
	try
	{
		// Textures
		m_textureHolder.acquire("PlayerMove", thor::Resources::fromFile<sf::Texture>("knight.png"));
		m_textureHolder.acquire("PlayerAttack", thor::Resources::fromFile<sf::Texture>("attack.png"));
		m_textureHolder.acquire("PlayerDie", thor::Resources::fromFile<sf::Texture>("die.png"));
		m_textureHolder.acquire("EnemyWalk", thor::Resources::fromFile<sf::Texture>("Enemy.png"));
		m_textureHolder.acquire("EnemyAttack", thor::Resources::fromFile<sf::Texture>("EnemyAttack.png"));
		m_textureHolder.acquire("Blood", thor::Resources::fromFile <sf::Texture>("blood.png"));
		m_textureHolder.acquire("Ghost", thor::Resources::fromFile <sf::Texture>("ghost.png"));
		m_textureHolder.acquire("Ectoplasm", thor::Resources::fromFile <sf::Texture>("ectoplasm.png"));
		m_textureHolder.acquire("Boom", thor::Resources::fromFile <sf::Texture>("boom.png"));
		m_textureHolder.acquire("Block", thor::Resources::fromFile <sf::Texture>("blocks.png"));
		m_textureHolder.acquire("Goal", thor::Resources::fromFile <sf::Texture>("goal.png"));
		m_textureHolder.acquire("Back", thor::Resources::fromFile <sf::Texture>("background.png"));
		m_textureHolder.acquire("MountainBack", thor::Resources::fromFile <sf::Texture>("ASSETS\\TEXTURES\\background.png"));
		m_textureHolder.acquire("Smoke", thor::Resources::fromFile <sf::Texture>("blood.png"));
		m_textureHolder.acquire("Bomb", thor::Resources::fromFile <sf::Texture>("bomb3.png"));

		// Sounds
		m_soundHolder.acquire("gui", thor::Resources::fromFile<sf::SoundBuffer>("guiSound.wav"));
		m_soundHolder.acquire("Boom", thor::Resources::fromFile<sf::SoundBuffer>("boom.wav"));
		m_soundHolder.acquire("Slash", thor::Resources::fromFile<sf::SoundBuffer>("slash2.wav"));
		m_soundHolder.acquire("Jump", thor::Resources::fromFile<sf::SoundBuffer>("jump.wav"));
		m_soundHolder.acquire("Walk", thor::Resources::fromFile<sf::SoundBuffer>("walking3.wav"));
		m_soundHolder.acquire("Pickup", thor::Resources::fromFile<sf::SoundBuffer>("pickup.wav"));
		m_soundHolder.acquire("Hit", thor::Resources::fromFile<sf::SoundBuffer>("hit.wav"));
		m_soundHolder.acquire("Ghost", thor::Resources::fromFile<sf::SoundBuffer>("ghost.wav"));
	}
	catch(thor::ResourceLoadingException& e)
	{
		std::cout << e.what() << std::endl;
	}
}