#include "PauseMenu.h"

Pause::Pause(float width, float height, Game & game, sf::RenderWindow & window):
	m_game(&game),
	m_window(window)
{
	m_itemSelected = false;
	//m_label.setUnderLined();
	m_widgets[0] = new Button("Continue", (width / 0.60f), float(height / (MAX_ITEMS - 0.5f) * 1.0f));
	m_widgets[0]->getFocus();
	m_widgets[1] = new Button("Quit", (width / 0.60f), (height / (MAX_ITEMS - 0.5f) * 1.5));  //dynamic placements

	m_widgets[0]->Enter = std::bind(&Pause::GoToPlay, this); //func bind
	m_widgets[1]->Enter = std::bind(&Pause::EndGame, this);
	m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	m_background.setFillColor(sf::Color(0, 0, 0, 125));

	m_selectedItemIndex = 0; //start at top 

	m_gui.vertical = true; //control scheme

	//add ui elements to gui
	for each (Widget* var in m_widgets)
	{
		m_gui.addWidget(var);
	}
	//m_gui.addLabel(&m_label);


}

Pause::~Pause()
{
	for each(Widget* var in m_widgets)
	{
		delete var;
	}
}


void Pause::draw()
{
	//m_window.draw(m_sprite);
	m_window.draw(m_background);
	m_gui.draw(m_window);
}

void Pause::update()
{
	m_gui.update(m_selectedItemIndex, MAX_ITEMS);
	
}

void Pause::GoToPlay()
{
	m_game->setGameState(GameState::Play);
}

void Pause::EndGame()
{
	m_game->setGameState(GameState::MainMenu);
	m_game->loadLevel("level.txt");
}

void Pause::resetPosition()
{
	sf::Vector2f halfScale(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
	m_background.setPosition(m_window.getView().getCenter() - halfScale);

	m_widgets[0]->updatePosition(m_window.getView().getCenter() + sf::Vector2f(-100, -100));
	m_widgets[1]->updatePosition(m_window.getView().getCenter() + sf::Vector2f(-100, 0));
}
