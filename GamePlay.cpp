#include "GamePlay.h"
#include "GameOver.h"
#include "PauseGame.h"
#include<SFML/Window/Event.hpp>
#include<stdlib.h>
#include <iostream>
#include<time.h>






GamePlay::GamePlay(shared_ptr<_Context>& m_context) :m_context(m_context)
,m_snakeDirection({ 16.f, 0.f }),m_elapsosedTime(Time::Zero), m_score(3) ,enemy_speed(0.5f)
,enemy_direction(-1,-1), enemy2_direction(0, -1)
{
	
	srand(time(nullptr));
}

GamePlay::~GamePlay() {
}

void GamePlay::inti() 
{
	fileToVec(".\Sprites\Map.txt");


	m_context->m_assets->AddTexture(AssetsID::GRASS,"Sprites/grass.png", true);

	m_context->m_assets->AddTexture(AssetsID::WALL,"Sprites/Wall.png",true);
	
	m_context->m_assets->AddTexture(AssetsID::FOOD,"Sprites/FoodApple.png");

	m_context->m_assets->AddTexture(AssetsID::SNAKE, "Sprites/snake.png");

	m_context->m_assets->AddTexture(AssetsID::POWERUP, "Sprites/ScorePower.png");

	m_context->m_assets->AddTexture(AssetsID::POWERDOWN, "Sprites/WrongFlage.png");

	m_context->m_assets->AddTexture(AssetsID::ENEMY, "Sprites/enemy.png");

	m_enemy.setTexture(m_context->m_assets->GetTexture(AssetsID::ENEMY));

	m_context->m_assets->AddTexture(AssetsID::ENEMY2, "Sprites/enemy2.png");

	m_enemy2.setTexture(m_context->m_assets->GetTexture(AssetsID::ENEMY2));
	m_enemy2.setPosition(300,280);

	m_enemy.setPosition(580, 280);


	m_wrong.setTexture(m_context->m_assets->GetTexture(AssetsID::POWERDOWN));
	m_wrong.setPosition( 320 / 2, 170 / 2);
	m_power.setTexture(m_context->m_assets->GetTexture(AssetsID::POWERUP));
	m_power.setPosition(200 / 2, 220 / 2);
	m_grass.setTexture(m_context->m_assets->GetTexture(AssetsID::GRASS));

	m_snake.Init(m_context->m_assets->GetTexture(AssetsID::SNAKE));

	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	for (auto& wall : m_walls) {
	
		wall.setTexture(m_context->m_assets->GetTexture(AssetsID::WALL));
	}
	

	m_walls[0].setTextureRect({ 0,0,640,16});
	m_walls[1].setTextureRect({ 0,0,640,16 });
	m_walls[1].setPosition(0,340-16);

	m_walls[2].setTextureRect({ 0,0,16,340 });
	m_walls[3].setTextureRect({ 0,0,16,340});
	m_walls[3].setPosition(640-16,0);

	m_food.setTexture(m_context->m_assets->GetTexture(AssetsID::FOOD));
	m_food.setScale(0.4f, 0.4f);
	m_food.setPosition(640 / 2, 340 / 2);

	m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_scoreText.setString("Score : " + to_string(m_score));
	
	
}

void GamePlay::processInput(){
	Event event;
	while (m_context->m_window->pollEvent(event))
	{

		if (event.type == Event::Closed) {
			m_context->m_window->close();
		}
		else if (event.type == Event::KeyPressed) {
			Vector2f newDirection = m_snakeDirection;

			switch (event.key.code)
			{
			case Keyboard::Up:
				newDirection = { 0.f,-16.f };
				break;
			case Keyboard::Down:
				newDirection = { 0.f,16.f };
				break;
			case Keyboard::Left:
				newDirection = { -16.f,0.f };
				break;
			case Keyboard::Right:
				newDirection = { 16.f,0.f };
				break;
			case Keyboard::Escape:
				m_context->m_state->Add(make_unique<PauseGame>(m_context));
				break;
			default:
				break;
			}

			if (abs(m_snakeDirection.x) != abs(newDirection.x) || 
				abs(m_snakeDirection.y) != abs(newDirection.y))
			{
				m_snakeDirection = newDirection;
			}
		}

	}
}

void GamePlay::Update(sf::Time deltaTime) {
	m_elapsosedTime += deltaTime;


	m_enemy.setPosition(m_enemy.getPosition()+enemy_direction*enemy_speed);

	m_enemy2.setPosition(m_enemy2.getPosition() + enemy2_direction * enemy_speed);



	for (auto& wall : m_walls) {
		
		if(wall.getGlobalBounds().intersects(m_enemy2.getGlobalBounds())) {

			enemy2_direction *= -1.f;
		}
		if(wall.getGlobalBounds().intersects(m_enemy.getGlobalBounds())) {

			enemy_direction *= -1.f;
		}

	}
	if (m_snake.IsOn(m_enemy)|| m_snake.IsOn(m_enemy2)) {
		m_context->m_state->Add(make_unique<GameOver>(m_context), true);
	}
	if (m_elapsosedTime.asSeconds()>0.1) {
		
		for (auto& wall : m_walls) {
			if (m_snake.IsOn(wall)) {
				
				m_context->m_state->Add(make_unique<GameOver>(m_context), true);
				break;
			}
		
		}
		if (m_snake.IsOn(m_power)) {
			int x = 0, y = 0;

			m_snake.Grow(m_snakeDirection);
			m_snake.Grow(m_snakeDirection);
			x = rand() % 600;
			y = rand() % 300;
			if (x >= 600) {
				x = x - (16 * 2);
			}
			if (x <= 40)
			{
				x = x + (16 * 2);

			}
			if (y >= 300) {
				y = y - (16 * 2);
			}
			if (y <= 40)
			{
				y = y + (16 * 2);
			}
			m_score += 2;
			m_scoreText.setString("Score : " + to_string(m_score));

			m_power.setPosition(x, y);
		}

		if (m_snake.IsOn(m_wrong)) {
			int x = 0, y = 0;
			

			x = rand() % 600;
			y = rand() % 300;
			if (x >= 600) {
				x = x - (16 * 2);
			}
			if (x <= 40)
			{
				x = x + (16 * 2);

			}
			if (y >= 300) {
				y = y - (16 * 2);
			}
			if (y <= 40)
			{
				y = y + (16 * 2);
			}
		bool shrink_status =	m_snake.Shrink();
		
		if (m_score==0) {
				m_context->m_state->Add(make_unique<GameOver>(m_context), true);
				
		}
		else {
			m_score--;
			m_scoreText.setString("Score : " + to_string(m_score));
			m_wrong.setPosition(x, y);
		}

		}
		if (m_snake.IsOn(m_food)) {

			m_snake.Grow(m_snakeDirection);
			int x = 0, y = 0;
			int xPos, yPos;
			
			x = rand() % 600; //m_context->m_window->getSize().x;
			y = rand() % 300; // m_context->m_window->getSize().y;
			if (x >= 600) {
				x = x - (16*2);
			}
			if (x <=40)
			{
				x = x + (16 * 2);

			}
			if (y >=300) {
				y = y - (16 * 2);
			}
			if (y <= 40)
			{
				y= y+ (16 * 2);
			}
			//x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 16, rand() % m_context->m_window->getSize().x - 2 * 16);
			m_score++;
			m_scoreText.setString("Score : " + to_string(m_score));
			m_food.setPosition(x, y);
		}

		/*if (m_snake.IsSelfIntersecting()) {
			m_context->m_state->Add(make_unique<GameOver>(m_context), true);
		}*/
		else {
		
		m_snake.Move(m_snakeDirection);
		
		}
		

		m_elapsosedTime = Time::Zero;
	
	}
}
void GamePlay::Darw(){
	
	m_context->m_window->clear();
	m_context->m_window->draw(m_grass);
	for (auto& wall : m_walls) {

		m_context->m_window->draw(wall);
	}
	m_context->m_window->draw(m_snake);
	m_context->m_window->draw(m_wrong);
	m_context->m_window->draw(m_food);
	m_context->m_window->draw(m_scoreText);
	m_context->m_window->draw(m_enemy);
	m_context->m_window->draw(m_enemy2);
	m_context->m_window->draw(m_power);

	m_context->m_window->display();
}

void GamePlay::fileToVec(string filePath)
{
	std::string line;
	std::ifstream infile(filePath);

	while (std::getline(infile, line)) {
		std::vector<char> row;

		for (char& c : line) {
			if (c != ',') {
				row.push_back(c);
			}
		}
		maze.push_back(row);
	}
}

void GamePlay::start() {

}
void GamePlay::pause() {

}