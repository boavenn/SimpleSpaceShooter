#include "Alien.hpp"

Alien::Alien(float max_health)
{
	sprite.setTexture(ResourceManager::get().textures.get("aliens"));
	this->max_health = max_health;
	current_health = max_health;
}

Alien::~Alien()
{
	animations.clear();
}
