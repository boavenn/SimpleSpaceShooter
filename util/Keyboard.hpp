#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Keyboard
{
public:
	Keyboard();

	void updateKeys(float dt);
	bool& getKeyStatus(unsigned keyCode);

private:
	std::array<bool, 128> key_status;
	std::array<float, 128> timers;
	std::array<float, 128> gaps;
};

