#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include<string>


class HUD {

public:
	HUD();
	void update(sf::View playerView);
	void draw(sf::RenderWindow &m_window);
	void increaseHealth();
	void decreaseHealth();
	void setHealth(int num);
	int getHealth();
	int getBombNum();
	void setBombNum(int num);
	void setScore(int num);
	void resetScore();

	void increaseBombs();

	void resetBools();
private:
	void manageHealthAnimations(sf::RenderWindow &m_window);

	sf::Font m_font;

	sf::Texture m_lifeTexture1;
	sf::Texture m_lifeTexture2;
	sf::Texture m_lifeTexture3;
	sf::Texture m_lifeTexture4;
	sf::Sprite m_3lifeBar;
	sf::Sprite m_2lifeBar;
	sf::Sprite m_1lifeBar;
	sf::Sprite m_0lifeBar;

	bool healthUp;
	bool healthDown;

	float m_3alpha = 255;
	float m_2alpha = 255;
	float m_1alpha = 255;
	float m_0alpha = 255;
	sf::Text m_scoreText;

	int health;

	float alphaChange;

	//temp
	bool press = false;

	sf::Texture m_bombTexture;
	sf::Sprite m_bombSprite;
	int bombNum;
	int score;
	sf::Text m_bombCount;
};