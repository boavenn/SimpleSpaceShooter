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

bool Alien::gotHitBy(Projectile* proj)
{
	sf::Vector2f pos = proj->getPosition();
	if (pos.x > this->left().x && pos.x < this->right().x && pos.y > this->top().y && pos.y < this->bottom().y)
	{
		current_health -= proj->getDamage();
		got_hit = true;
		if (current_health <= 0)
		{
			should_die = true;
		}
		return true;
	}
	return false;
}
