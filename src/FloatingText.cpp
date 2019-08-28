#include "..\inc\FloatingText.h"
#include <iostream>

FloatingText::FloatingText(const std::string info, sf::Vector2f pos, sf::Color c) : text(info, ResourceManager::get().fonts.get("VCR_OSD_MONO_1.001"), 18)
{
	this->livingTime = livingTime;
	color = c;
	text.setFillColor(color);
	text.setPosition(pos);
}

void FloatingText::update(float deltaTime)
{
	totalTime += deltaTime;
	totalMovementTime += deltaTime;

	if (totalMovementTime >= movementTick)
	{
		totalMovementTime -= movementTick;

			if(color.r > 100)
				color.r -= 40;
			if(color.g > 100)
				color.g -= 40;
			if(color.b > 100)
				color.b -= 40;

		text.setFillColor(color);
		text.setPosition({ text.getPosition().x, text.getPosition().y - 2.f });
	}

	if (totalTime >= livingTime)
		died = true;
}
