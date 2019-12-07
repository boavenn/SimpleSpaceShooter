#include "Pickup.hpp"

Pickup::Pickup(sf::Vector2f init_pos, sf::Vector2f velocity)
{
	this->velocity = velocity;

	sprite.setTexture(ResourceManager::get().textures.get("pickups"));
	sprite.setOrigin({ 15.f, 15.f });
	sprite.setPosition(init_pos);
}

Pickup::~Pickup()
{
	delete animation;
}

void Pickup::update(float dt)
{
	sprite.move(velocity * dt);
	if (animation != nullptr)
	{
		sprite.setTextureRect(animation->update(dt));
	}
}

void Pickup::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}
