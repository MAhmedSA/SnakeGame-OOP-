#pragma once
#include<memory>
#include<SFML/Graphics/RenderWindow.hpp>
#include"AssetsMan.h"
#include "StateMan.h"
using namespace sf;


enum AssetsID {

	MAIN_FONT = 0,
	GRASS,
	FOOD,
	WALL,
	SNAKE,
	POWERUP,
	POWERDOWN,
	ENEMY,
	ENEMY2

};

struct _Context {

	unique_ptr<Engine::AssetsMan> m_assets;
	unique_ptr<Engine::StateMan> m_state;
	unique_ptr<RenderWindow> m_window;

	_Context() {
		m_assets = make_unique<Engine::AssetsMan>();
		m_state = make_unique<Engine::StateMan>();
		m_window = make_unique<RenderWindow>();
	}
};

class Game {

private:

	
	std::shared_ptr<_Context> m_context;
	
	const Time TIME_PER_SECOND = seconds(1.f / 60);

public:
	Game();
	~Game();

	void Run();
};