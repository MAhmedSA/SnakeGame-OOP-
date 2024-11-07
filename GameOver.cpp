#include "GameOver.h"
#include<SFML\Window\Event.hpp>
#include"GamePlay.h"
GameOver::GameOver(shared_ptr<_Context>& contetx) :m_context(contetx)
, m_isRetryButtonSelected(true),
m_isRetryButtonpressed(false),
m_isExitButtonSelected(false),
m_isExitButtonpressed(false)
{

}

GameOver::~GameOver() {

}

void GameOver::inti()
{
	//Game Title 
	m_context->m_assets->AddFont(AssetsID::MAIN_FONT, "./Font/Pacifico-Regular.ttf");
	m_gameOverTitle.setFont(m_context->m_assets->GetFont(AssetsID::MAIN_FONT));
	m_gameOverTitle.setString("Game Over !!");
	m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
	m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.f);

	//Play Button
	//m_context->m_assets->AddFont(MAIN_FONT, "./Font/Pacifico-Regular.ttf");
	m_retryButton.setFont(m_context->m_assets->GetFont(AssetsID::MAIN_FONT));
	m_retryButton.setString("Retry Game");
	m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2, m_retryButton.getLocalBounds().height / 2);
	m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f);
	m_retryButton.setCharacterSize(25);


	//Exit Button
	//m_context->m_assets->AddFont(MAIN_FONT, "./Font/Pacifico-Regular.ttf");
	m_exitButton.setFont(m_context->m_assets->GetFont(AssetsID::MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.f);
	m_exitButton.setCharacterSize(25);

}

void GameOver::processInput()
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
				if (!m_isRetryButtonSelected) {

					m_isRetryButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			case Keyboard::Down:
				if (!m_isExitButtonSelected) {

					m_isRetryButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			case Keyboard::Return:
				m_isRetryButtonpressed = false;
				m_isExitButtonpressed = false;

				if (m_isRetryButtonSelected) {
					m_isRetryButtonpressed = true;
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

void GameOver::Update(sf::Time deltaTime)
{
	if (m_isRetryButtonSelected) {
		m_retryButton.setFillColor(Color::Blue);
		m_exitButton.setFillColor(Color::White);
	}
	else {
		m_exitButton.setFillColor(Color::Blue);
		m_retryButton.setFillColor(Color::White);

	}
	if (m_isRetryButtonpressed) {

		//GamePlay state
		m_context->m_state->Add(std::forward<unique_ptr<GamePlay>>(make_unique<GamePlay>(m_context)), true);

	}
	else if (m_isExitButtonpressed) {
		//go to Exit State
		m_context->m_window->close();

	}
}

void GameOver::Darw()
{
	m_context->m_window->clear(Color::Black);
	m_context->m_window->draw(m_gameOverTitle);
	m_context->m_window->draw(m_retryButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();

}