#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include"Game.h"
#include"MainMenu.h"
using namespace std;



Game::Game():m_context(make_unique<_Context>()){

	m_context->m_window->create(VideoMode(640, 340),"Snake",Style::Close);
    m_context->m_state->Add(make_unique<MainMenu>(m_context));
}

Game::~Game() {


}

void Game::Run() {
    CircleShape shape(20.f);
    shape.setFillColor(sf::Color::Green);

    Clock clock;
    Time timeSinceLastFrame = Time::Zero;

   

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();
        while (timeSinceLastFrame > TIME_PER_SECOND) {
            timeSinceLastFrame -= TIME_PER_SECOND;

            
            m_context->m_state->processChangeState();
            
            m_context->m_state->GetCurrent()->processInput();
            
            m_context->m_state->GetCurrent()->Update(TIME_PER_SECOND);
            
            m_context->m_state->GetCurrent()->Darw();
        }
        
    }
}