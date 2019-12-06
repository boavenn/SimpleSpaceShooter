#include "StateManager.hpp"

StateManager::~StateManager()
{
	stack.clear();
}

void StateManager::pushState(std::unique_ptr<State> new_state, bool is_swapping, bool is_first)
{
	if (is_swapping)
		stack.pop_back();
	if (is_first && !stack.empty())
		stack.clear();

	stack.push_back(std::move(new_state));
	stack.back()->setPlace(stack.size() - 1);

	if (!is_swapping && !is_first)
		stack.back()->isConcurrent() = true;
}

void StateManager::popState(unsigned quantity)
{
	for (size_t i = 0; i < quantity; i++)
		if (!stack.empty())
			stack.pop_back();
}

bool StateManager::isEmpty()
{
	return stack.empty();
}

bool StateManager::isOnTop(State* state)
{
	return state == &getTop();
}

State& StateManager::getTop()
{
	return *stack.back();
}

State& StateManager::getPrevious(unsigned idx)
{
	return *stack[idx - 1];
}
