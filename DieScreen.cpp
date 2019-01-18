#include "DieScreen.h"

DieScreen::DieScreen(float width, float height, Game& game, sf::RenderWindow &window):
	m_game(&game),
	m_window(window)
{
	m_itemSelected = false;
	//m_label.setUnderLined();
	m_widgets[0] = new Button("Try Again", (width / 0.60f), float(height / (MAX_ITEMS - 0.5f) * 1.0f));
	m_widgets[0]->getFocus();
	m_widgets[0]->Enter = std::bind(&DieScreen::tryAgain, this); //func bind
	m_widgets[1] = new Button("Quit", (width / 0.60f), float(height / (MAX_ITEMS - 0.5f) * 1.0f));
	m_widgets[1]->Enter = std::bind(&DieScreen::EndGame, this); //func bind
	m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	m_background.setFillColor(sf::Color(255, 0, 0, 0));

	m_selectedItemIndex = 0; //start at top 

	m_gui.horizontal = true; //control scheme

						   //add ui elements to gui
	for each (Widget* var in m_widgets)
	{
		m_gui.addWidget(var);
	}




	//m_gui.addLabel(&m_label);
	transparency = 0;
	transparency2 = 0;

	if (!m_font.loadFromFile("Adventurer.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;
	}

	m_text.setFont(m_font);

	m_text.setCharacterSize(100);
	m_text.setString("You're Dead!");
	m_text.setPosition(sf::Vector2f(m_window.getSize().x / 3.5, m_window.getSize().y / 2.5));
	m_text.setFillColor(sf::Color(255, 255, 255, transparency));
	m_widgets[0]->updateFocusColor(sf::Color(255, 255, 255, 255));
	m_widgets[1]->updateFocusColor(sf::Color(255, 255, 255, 255));
	m_count = 0;
}

DieScreen::~DieScreen()
{
	for each(Widget* var in m_widgets)
	{
		delete var;
	}
}

void DieScreen::draw()
{
	m_window.draw(m_background);
	m_gui.draw(m_window);
	m_window.draw(m_text);
}

void DieScreen::update()
{

	sf::Vector2f halfScale(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

	if (transparency < 125)
	{
		transparency += 1.f;
		m_background.setFillColor(sf::Color(255, 0, 0, transparency));
		
	}

	if (transparency2 < 255)
	{

		transparency2 += 1.f;
		m_text.setFillColor(sf::Color(255, 255, 255, transparency2));
	}
	
	m_widgets[0]->updatePosition(m_window.getView().getCenter() + sf::Vector2f(-300, 200));
	m_widgets[1]->updatePosition(m_window.getView().getCenter() + sf::Vector2f(100, 200));

	m_text.setPosition(m_window.getView().getCenter()+ sf::Vector2f(-300,-100));
	m_background.setPosition(m_window.getView().getCenter()- halfScale);
	if (m_count > 120)
	{
		m_gui.update(m_selectedItemIndex, MAX_ITEMS);

	}
	else
	{
		m_count++;
	}
}

void DieScreen::EndGame()
{
	transparency = 0;
	transparency2 = 0;
	m_background.setFillColor(sf::Color(255, 0, 0, transparency));
	m_text.setFillColor(sf::Color(255, 255, 255, transparency2));
	m_game->setGameState(GameState::MainMenu);
	m_count = 0;
	m_selectedItemIndex = 0;
}

void DieScreen::tryAgain()
{
	transparency = 0;
	transparency2 = 0;
	m_background.setFillColor(sf::Color(255, 0, 0, transparency));
	m_text.setFillColor(sf::Color(255, 255, 255, transparency2));
	m_game->loadLevel("");
	m_game->setGameState(GameState::Play);
	m_count = 0;
	m_selectedItemIndex = 0;
}
