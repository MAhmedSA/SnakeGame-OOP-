#pragma once
#include<memory>
#include<array>
#include"State.h"
#include"Game.h"
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Text.hpp>
#include"Snake.h"
#include <fstream>


class GamePlay:public Engine::State
{

private:
	std::vector<std::vector<char> > maze;
	shared_ptr<_Context> m_context;
	Sprite m_grass;
	Sprite m_food;
	Sprite m_wrong;
	Sprite m_power;
	Sprite m_enemy;
	Sprite m_enemy2;
	float enemy_speed;
	Vector2f enemy_direction;
	Vector2f enemy2_direction;
	array<Sprite,4> m_walls;
	Snake m_snake;
	Vector2f m_snakeDirection;
	Time m_elapsosedTime;
	Text m_scoreText;
	int m_score;

public:
	GamePlay(shared_ptr<_Context>& m_context);
	~GamePlay();
	void inti()override;
	void processInput()override;
	void Update(sf::Time deltaTime)override;
	void Darw()override;
	void fileToVec(string filePath);
	void start()override;
	void pause()override;

};

