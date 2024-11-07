#pragma once

#include <SFML/System/Time.hpp>

namespace Engine {
class State
{
public:
	State() {};
	virtual ~State() {};

	virtual void inti() = 0;
	virtual void processInput() = 0;
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Darw() = 0;

	virtual void start() {};
	virtual void pause() {};
};
}

