#include "FloatingText.hpp"

FloatingText::FloatingText(const std::string info, sf::Vector2f pos, sf::Color c) : text(info, ResourceManager::get().fonts.get("MonospaceTypewriter"), 18)
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

		if (color.r > 100)
			color.r -= 20;
		if (color.g > 100)
			color.g -= 20;
		if (color.b > 100)
			color.b -= 20;

		text.setFillColor(color);
		text.setPosition({ text.getPosition().x, text.getPosition().y - 2.f });
	}

	if (totalTime >= livingTime)
		died = true;
}