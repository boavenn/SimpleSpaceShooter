#include "..\inc\Background.h"

Background::Background(float switchTime, sf::Vector2f pos, const std::string texName, bool fromRight)
{
	sprite.setTexture(ResourceManager::get().textures.get(texName));
	sprite.setPosition(pos);
	this->switchTime = switchTime;
	this->fromRight = fromRight;
	xSize = ResourceManager::get().textures.get(texName).getSize().x;
	ySize = ResourceManager::get().textures.get(texName).getSize().y;
}

void Background::update(float deltaTime)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime = 0.f;
		if (shift++ == 768)
			shift = 0;
	}

	if (fromRight)
		sprite.setTextureRect(sf::IntRect(0, 0 - shift, -1 * xSize, ySize));
	else
		sprite.setTextureRect(sf::IntRect(0, 0 - shift, xSize, ySize));
}
