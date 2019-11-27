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
	if (this->contains(proj))
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
