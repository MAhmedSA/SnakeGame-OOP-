#include "StateMan.h"
using namespace std;
using namespace sf;

Engine::StateMan::StateMan() :m_add(false), m_remove(false), m_replace(false) {}

Engine::StateMan::~StateMan() {
}

void Engine::StateMan::Add(unique_ptr<Engine::State> toAdd, bool replaced ) {
	
	m_add = true;
	//m_newState = move(toAdd);
	m_newState = move(toAdd);
	m_replace = replaced;

}

void Engine::StateMan::popCureent(){
	m_remove = true;
}

void Engine::StateMan::processChangeState() {

	if (m_remove && (!m_stateStack.empty())) {
		
		m_stateStack.pop();

		if (!m_stateStack.empty()) {
			m_stateStack.top()->start();
		}
		m_remove = false;

	}
	if (m_add) {

		if (m_replace && !m_stateStack.empty()) {
			m_stateStack.pop();
			m_replace = false;
		}
		if (!m_stateStack.empty()) {
			m_stateStack.top()->pause();

		}
		m_stateStack.push(move(m_newState));
		m_stateStack.top()->inti();
		m_stateStack.top()->start();
		m_add = false;
	}


}

unique_ptr<Engine::State> & Engine::StateMan::GetCurrent(){
	
	
	return (m_stateStack).top();
}


