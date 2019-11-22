#include "Keyboard.hpp"

Keyboard::Keyboard()
{
	std::fill(key_status.begin(), key_status.end(), false);
	std::fill(timers.begin(), timers.end(), 0.f);
	std::fill(gaps.begin(), gaps.end(), 0.2f);
	gaps[8] = 0.1f;
}

void Keyboard::updateKeys(float dt)
{
	for (size_t i = 0; i < key_status.size(); i++)
	{
		if (!key_status[i])
		{
			timers[i] += dt;
			if (timers[i] >= gaps[i])
			{
				key_status[i] = true;
				timers[i] = 0.f;
			}
		}
	}
}

bool& Keyboard::getKeyStatus(unsigned keyCode)
{
	return key_status[keyCode];
}
