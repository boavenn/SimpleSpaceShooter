#include "..\inc\FloatingText.h"
#include <iostream>

FloatingText::FloatingText(const std::string info, sf::Vector2f pos, sf::Color c) : text(info, ResourceManager::get().fonts.get("VCR_OSD_MONO_1.001"), 18)
{
	this->livingTime = livingTime;
	color = c;
	text.setFillColor(color);
	text.setPosition(pos);

	if (color == sf::Color::White)
		is_white = true;
	else
		is_white = false;
}

void FloatingText::update(float deltaTime)
{
	totalTime += deltaTime;
	totalMovementTime += deltaTime;
	if (totalMovementTime >= movementTick)
	{
		totalMovementTime -= movementTick;

		/*if (is_white)
		{
			color.r /= static_cast<sf::Uint8>(livingTime / movementTick);
			color.g /= static_cast<sf::Uint8>(livingTime / movementTick);
			color.b /= static_cast<sf::Uint8>(livingTime / movementTick);
		}
		else
		{*/
			if(color.r > 100)
				color.r -= 40;
			if(color.g > 100)
				color.g -= 40;
			if(color.b > 100)
				color.b -= 40;
		//}

		text.setFillColor(color);
		text.setPosition({ text.getPosition().x, text.getPosition().y - 2.f });
	}

	if (totalTime >= livingTime)
		died = true;
}
