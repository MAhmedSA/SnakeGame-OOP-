#pragma once
#include "State.h"
#include<memory>
#include<stack>
#include<iostream>
using namespace std;
using namespace sf;


namespace Engine {
	class StateMan {

	private:
		stack<unique_ptr<State>> m_stateStack;

		unique_ptr<State> m_newState;

		bool m_replace, m_add, m_remove;

	public:

		 StateMan();
		~StateMan();
		
		

		void Add(unique_ptr<State> toAdd, bool replaced = false);
		void popCureent();
		void processChangeState();
		unique_ptr<State> & GetCurrent();

	};
}


