#include "..\inc\Pickup.h"

Pickup::Pickup(sf::Vector2f pos)
{
	velocity.y = float(rand.getIntInRange(150, 250));
	type = static_cast<PickupType>(rand.getIntInRange(0, 8));
	sprite.setTexture(ResourceManager::get().textures.get("pickups"));
	sprite.setTextureRect(setRect(type));
	sprite.setOrigin({ 10.f,10.f });
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
	int type_no = static_cast<int>(type);
	int row = (type_no / 5) * 20;
	int pos_x = (type_no % 5) * 20;
	return sf::IntRect(pos_x, row, 20, 20);
}
