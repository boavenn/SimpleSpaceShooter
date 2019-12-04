#pragma once
#include "State.hpp"

class StateManager
{
public:
	StateManager() = default;
	~StateManager();
	void pushState(std::unique_ptr<State> new_state, bool is_swapping = 0, bool is_first = 0);
	void popState(unsigned quantity = 1);
	bool isEmpty();
	int size() { return stack.size(); }
	State& getTop();
	State& getPrevious(unsigned idx);

private:
	std::vector<std::unique_ptr<State>> stack;
};

