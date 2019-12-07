#include "Alien.hpp"
#include <cmath>

constexpr auto M_PI = 3.14159265358979323846;

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
	diving_tick = R::nextFloat(200, 300) / 100.f;
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

void Alien::activateBerserkMode()
{
	in_berserk_mode = true;
	int r = R::nextInt(0, 101);
	if (r <= 50)
		berserk_mode_dir = -1;
	else
		berserk_mode_dir = 1;
	fire_chance += 20;
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

void Alien::checkDive(float dt)
{
	diving_timer += dt;
	if (diving_timer >= diving_tick)
	{
		int rand = R::nextInt(0, 101);
		if (rand <= dive_chance / 2 || rand >= 100 - dive_chance / 2)
		{
			is_diving = true;
			int r = R::nextInt(0, 51);
			dive_sign = r < 25 ? 1 : -1;
			fire_chance += 15;
		}

		diving_timer -= diving_tick;
		
	}
}

void Alien::tryDive(float dt)
{
	diving_time += dt;

	if (diving_time >= diving_time_max)
	{
		sprite.setPosition(target_pos);
		velocity = { 0.f, 0.f };
		is_diving = false;
		diving_tick = R::nextFloat(200, 300) / 100.f;
		diving_time = 0.f;
		fire_chance -= 15;
	}
	else
	{
		int y = WindowProperties::getHeight() - int(target_pos.y);
		velocity.x = dive_sign * 144.f * float(cos(2 * M_PI * diving_time / diving_time_max));
		velocity.y = R::nextFloat(y - 100, y + 100) * float(sin(2.f * M_PI * diving_time / diving_time_max));
	}
}

void Alien::checkBerserkMode(float dt)
{
	berserk_mode_timer += dt;
	if (berserk_mode_timer >= berserk_mode_tick)
	{
		if(!change_dir)
			velocity = { berserk_mode_dir * R::nextFloat(200, 300), R::nextFloat(200, 350) };
		else
		{
			velocity.x += berserk_mode_dir * 50.f;
			if (berserk_mode_dir < 0 && velocity.x <= -200)
				change_dir = false;
			else if (berserk_mode_dir > 0 && velocity.x >= 200)
				change_dir = false;
		}

		if (!change_dir && R::nextInt(0, 101) <= 20)
		{	
			berserk_mode_dir = -berserk_mode_dir;
			change_dir = true;
		}

		berserk_mode_timer -= berserk_mode_tick;
	}

	if (sprite.getPosition().y > float(WindowProperties::getHeight()))
		sprite.setPosition({ sprite.getPosition().x, -50.f });
	if (sprite.getPosition().x < 150.f)
		sprite.setPosition({ float(WindowProperties::getWidth()) - 150.f, sprite.getPosition().y });
	else if (sprite.getPosition().x > float(WindowProperties::getWidth()) - 150.f)
		sprite.setPosition({ 150.f, sprite.getPosition().y });
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
