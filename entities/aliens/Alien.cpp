#include "Alien.hpp"
#include <iostream>

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

bool Alien::gotHitBy(Projectile* proj)
{
	sf::Vector2f pos = proj->getPosition();
	if (pos.x > this->left() && pos.x < this->right() && pos.y > this->top() && pos.y < this->bottom())
	{
		current_health -= proj->getDamage();
		got_hit = true;
		std::cout << "Got hit" << std::endl;
		if (current_health <= 0)
		{
			should_die = true;
		}
		return true;
	}
	return false;
}
