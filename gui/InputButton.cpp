#include "InputButton.hpp"

InputButton::InputButton(const sf::Vector2f& size, const sf::Vector2f& pos) : Button(size, pos)
{

}

bool& InputButton::isInputActive()
{
	return is_input_active;
}

void InputButton::checkUserInput(float dt, sf::Event e)
{

	if (is_input_active)
	{
		keyboard.updateKeys(dt);

		if (e.type == sf::Event::TextEntered)
		{
			unsigned char keyCode = e.text.unicode;
			if (keyCode == 13) // Enter
			{
				is_input_active = false;
				return;
			}
			else if (keyCode == 8 && !input.empty()) // Backspace
			{
				if (keyboard.getKeyStatus(keyCode))
				{
					input.pop_back();
					setText(input);
					centerText();
					keyboard.getKeyStatus(keyCode) = false;
				}
			}
			else if (text.getGlobalBounds().width + 40 <= box.getGlobalBounds().width && ((keyCode >= 44 && keyCode <= 57) || (keyCode >= 65 && keyCode <= 90) || (keyCode >= 97 && keyCode <= 122) || keyCode == 32))
			{
				if (keyboard.getKeyStatus(keyCode))
				{
					input.push_back(keyCode);
					setText(input);
					centerText();
					keyboard.getKeyStatus(keyCode) = false;
				}
			}
		}
	}
}

void InputButton::resetInput()
{
	input = "";
	text.setString("");
}

const std::string& InputButton::getInput()
{
	return input;
}
