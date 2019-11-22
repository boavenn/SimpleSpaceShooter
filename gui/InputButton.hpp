#pragma once
#include "Button.hpp"
#include "..//util/Keyboard.hpp"

class InputButton : public Button
{
public:
	InputButton(const sf::Vector2f& size, const sf::Vector2f& pos);

	bool& isInputActive();
	void checkUserInput(float dt, sf::Event e);
	const std::string& getInput();

private:
	std::string input = "";
	bool is_input_active = false;
	Keyboard keyboard;
};

