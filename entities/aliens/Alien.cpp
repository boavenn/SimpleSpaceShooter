#include "Alien.hpp"

Alien::Alien(float max_health)
{
	sprite.setTexture(ResourceManager::get().textures.get("aliens"));
	this->max_health = max_health;
	current_health = max_health;

	fire_tick = R::nextFloat(100, 200) / 100.f;
	fire_delay = R::nextFloat(0, (int)((fire_tick / 2.f) * 100)) / 100.f;
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

void Alien::tryFire(float dt)
{
	if (should_fire)
	{
		fire_delay_timer += dt;
		if (fire_delay_timer >= fire_delay)
		{
			firing = true;
			should_fire = false;
			fire_delay_timer = 0.f;
		}
	}

	fire_timer += dt;
	if (fire_timer >= fire_tick)
	{
		int rand = R::nextInt(0, 101);
		if (rand <= fire_chance / 2 || rand >= 100 - fire_chance / 2)
			should_fire = true;

		fire_timer -= fire_tick;
		fire_delay = R::nextFloat(0, (int)((fire_tick / 2.f) * 100)) / 100.f;
	}
}
