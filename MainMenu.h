#pragma once
#include<memory>
#include"State.h"
#include"Game.h"
#include<SFML/Graphics/Text.hpp>


class MainMenu :public Engine::State
{
private:

	shared_ptr<_Context> m_context;
	Text m_gameTitle;

	Text m_exitButton;
	Text m_playButton;

	bool m_isPlayButtonSelected;
	bool m_isPlayButtonpressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonpressed;

public:
	MainMenu(shared_ptr<_Context>& contetx);
	~MainMenu();

	 void inti()override;
	 void processInput()override;
	 void Update(sf::Time deltaTime)override;
	 void Darw() override;
};

