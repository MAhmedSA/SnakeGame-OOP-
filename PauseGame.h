#pragma once
#include"State.h"
#include"Game.h"
#include<SFML/Graphics/Text.hpp>

class PauseGame : public Engine::State
{

private:

	shared_ptr<_Context> m_context;
	Text m_pauseTitle;


public:

	PauseGame(shared_ptr<_Context>& m_context);
	~PauseGame();

	void inti()override;
	void processInput()override;
	void Update(sf::Time deltaTime)override;
	void Darw()override;

};




