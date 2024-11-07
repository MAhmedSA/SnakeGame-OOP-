#include "MainMenu.h"
#include"GamePlay.h"
#include<SFML/Window/Event.hpp>

MainMenu::MainMenu(shared_ptr<_Context>& contetx):m_context(contetx) 
,m_isPlayButtonSelected(true),
m_isPlayButtonpressed(false),
m_isExitButtonSelected(false),
m_isExitButtonpressed(false)
{
	
}

MainMenu::~MainMenu() {

}

void MainMenu::inti()
{
	//Game Title 
	m_context->m_assets->AddFont(AssetsID::MAIN_FONT,"./Font/Pacifico-Regular.ttf");
	m_gameTitle.setFont(m_context->m_assets->GetFont(AssetsID::MAIN_FONT));
	m_gameTitle.setString("Snake Game");
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width/2, m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2-150.f);
	
	//Play Button
	//m_context->m_assets->AddFont(MAIN_FONT, "./Font/Pacifico-Regular.ttf");
	m_playButton.setFont(m_context->m_assets->GetFont(AssetsID::MAIN_FONT));
	m_playButton.setString("Play");
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2-25.f);
	m_playButton.setCharacterSize(25);
	

	//Exit Button
	//m_context->m_assets->AddFont(MAIN_FONT, "./Font/Pacifico-Regular.ttf");
	m_exitButton.setFont(m_context->m_assets->GetFont(AssetsID::MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.f);
	m_exitButton.setCharacterSize(25);

}

void MainMenu::processInput()
{
	Event event;
	while (m_context->m_window->pollEvent(event))
	{

		if (event.type == Event::Closed) {
			m_context->m_window->close();
		}
		else if (event.type == Event::KeyPressed) {
		
			switch (event.key.code)
			{
				case Keyboard::Up:
					if (!m_isPlayButtonSelected) {
						
						m_isPlayButtonSelected = true;
						m_isExitButtonSelected = false;
					}
					break;
				case Keyboard::Down:
					if (!m_isExitButtonSelected) {

						m_isPlayButtonSelected = false;
						m_isExitButtonSelected = true;
					}
					break;
				case Keyboard::Return:
					m_isPlayButtonpressed = false;
					m_isExitButtonpressed = false;

					if (m_isPlayButtonSelected) {
						m_isPlayButtonpressed = true;
					}
					else {
						m_isExitButtonpressed = true;
					}
					break;
				default:
					break;
			}
		
		}

	}
	

}

void MainMenu::Update(sf::Time deltaTime)
{
	if (m_isPlayButtonSelected) {
		m_playButton.setFillColor(Color::Blue);
		m_exitButton.setFillColor(Color::White);
	}
	else {
		m_exitButton.setFillColor(Color::Blue);
		m_playButton.setFillColor(Color::White);
		
	}
	if (m_isPlayButtonpressed) {
		
		//GamePlay state
		m_context->m_state->Add(std::forward<unique_ptr<GamePlay>>(make_unique<GamePlay>(m_context)) , true);
		
	}
	else if(m_isExitButtonpressed) {
		//go to Exit State
		m_context->m_window->close();

	}
}

void MainMenu::Darw()
{
	m_context->m_window->clear(Color::Black);
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();

}