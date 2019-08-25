#include "..\inc\Pickup.h"

Pickup::Pickup(sf::Vector2f pos)
{
	velocity.y = float(rand.getIntInRange(150, 250));
	type = static_cast<PickupType>(rand.getIntInRange(1, 6));
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
	switch (type) // TODO: automate this, it's easy
	{
	case speedInc:
		return sf::IntRect(0, 0, 20, 20);
		break;
	case magazineSizeInc:
		return sf::IntRect(20, 0, 20, 20);
		break;
	case reloadSpeedInc:
		return sf::IntRect(40, 0, 20, 20);
		break;
	case bulletSpeedInc:
		return sf::IntRect(60, 0, 20, 20);
		break;
	case liveAdd:
		return sf::IntRect(80, 0, 20, 20);
		break;
	default:
		return sf::IntRect(10, 0, 20, 20);
		break;
	}
}
