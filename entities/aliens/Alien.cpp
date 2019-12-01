#include "Alien.hpp"
#include <cmath>

Alien::Alien(sf::Vector2f pos, float max_health, int direction, float delay)
{
	sprite.setTexture(ResourceManager::get().textures.get("aliens"));

	this->ascend_delay = delay;
	this->max_health = max_health;
	current_health = max_health;
	target_pos = pos;
	ascend_direction = static_cast<Alien::AscendDir>(direction);
	setInitPos(ascend_direction);

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

void Alien::tryAscend(float dt)
{
	if (ascend_delay_timer >= ascend_delay)
	{
		ascend_timer += dt;
		sprite.move(ascending_velocity * dt);

		if (ascend_timer >= ascend_time)
		{
			sprite.setPosition(target_pos);
			is_ascending = false;
		}
	}
	else
		ascend_delay_timer += dt;
}

void Alien::setInitPos(AscendDir dir)
{
	float dis = 1000.f;

	switch (dir)
	{
	case Alien::AscendDir::SOUTH:
		init_pos = { target_pos.x, target_pos.y + dis };
		break;
	case Alien::AscendDir::SOUTHEAST:
		init_pos = { target_pos.x - dis, target_pos.y + dis };
		break;
	case Alien::AscendDir::EAST:
		init_pos = { target_pos.x - dis, target_pos.y };
		break;
	case Alien::AscendDir::NORTHEAST:
		init_pos = { target_pos.x - dis, target_pos.y - dis };
		break;
	case Alien::AscendDir::NORTH:
		init_pos = { target_pos.x, target_pos.y - dis };
		break;
	case Alien::AscendDir::NORTHWEST:
		init_pos = { target_pos.x + dis, target_pos.y - dis };
		break;
	case Alien::AscendDir::WEST:
		init_pos = { target_pos.x + dis, target_pos.y };
		break;
	case Alien::AscendDir::SOUTHWEST:
		init_pos = { target_pos.x + dis, target_pos.y + dis };
		break;
	}

	ascending_velocity = (target_pos - init_pos) / ascend_time;
}
