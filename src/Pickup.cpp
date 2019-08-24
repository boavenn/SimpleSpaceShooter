#include "..\inc\Pickup.h"

Pickup::Pickup(sf::Vector2f pos)
{
	type = static_cast<PickupType>(rand.getIntInRange(1, 2));
	sprite.setTexture(ResourceManager::get().textures.get("pickups"));
	sprite.setTextureRect(setRect(type));
	sprite.setOrigin({ 20.f,20.f });
	sprite.setPosition(pos);
}

void Pickup::update(float deltaTime)
{
	sprite.move(velocity * deltaTime);
}

void Pickup::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

sf::IntRect Pickup::setRect(PickupType type)
{
	switch (type)
	{
	case speedInc:
		return sf::IntRect(0, 0, 20, 20);
		break;
	}
}
