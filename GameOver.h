#pragma once
#include<SFML/Graphics/Text.hpp>
#include "Game.h"
#include "State.h"

class GameOver :public Engine::State
{

private:

	shared_ptr<_Context> m_context;
	Text m_gameOverTitle;

	Text m_retryButton;
	Text m_exitButton;

	bool m_isRetryButtonSelected;
	bool m_isRetryButtonpressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonpressed;

public:
	GameOver(shared_ptr<_Context>& contetx);
	~GameOver();

	void inti()override;
	void processInput()override;
	void Update(sf::Time deltaTime)override;
	void Darw() override;
};




