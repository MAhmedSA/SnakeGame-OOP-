#include "PauseGame.h"
#include<SFML\Window\Event.hpp>
PauseGame::PauseGame(shared_ptr<_Context>& context):m_context(context)
{

}
PauseGame::~PauseGame() {}

void PauseGame::inti()
{
	//Title 
	m_pauseTitle.setFont(m_context->m_assets->GetFont(AssetsID::MAIN_FONT));
	m_pauseTitle.setString("Paused");
	m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2, m_pauseTitle.getLocalBounds().height / 2);
	m_pauseTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 );

}

void PauseGame::processInput()
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
			case Keyboard::Escape:
				m_context->m_state->popCureent();
				break;
			default:
				break;
			}

		}

	}


}

void PauseGame::Update(sf::Time deltaTime)
{
}

void PauseGame::Darw()
{
	m_context->m_window->draw(m_pauseTitle);
	m_context->m_window->display();
}
