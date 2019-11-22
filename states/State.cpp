#include "State.hpp"

void State::setPlace(unsigned idx)
{
	place_on_stack = idx;
}

bool& State::isConcurrent()
{
	return is_concurrent;
}

bool State::isAbleToInput(float dt)
{
	if (input_ability)
		return true;
	else
	{
		transition_elapsed += dt;
		if (transition_elapsed >= transition_freeze_time)
		{
			transition_elapsed = 0.f;
			input_ability = true;
		}
		return input_ability;
	}
}
