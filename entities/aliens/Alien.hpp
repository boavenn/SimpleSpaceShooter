#pragma once
#include "../Entity.hpp"
#include "../Projectile.hpp"
#include "../../res/ResourceManager.hpp"
#include "../util/Random.hpp"
#include "../util/SoundMaking.hpp"

typedef Random R;

class Alien : public Entity, public SoundMaking
{
public:
	enum class AscendDir
	{
		SOUTH, SOUTHEAST, EAST, NORTHEAST, NORTH, NORTHWEST, WEST, SOUTHWEST
	};

public:
	Alien(sf::Vector2f pos, float max_health, int direction, float delay);
	~Alien();
	bool gotHitBy(Projectile* proj);
	bool shouldDie() { return should_die; }
	bool isFiring() { return firing; }
	virtual std::vector<Projectile*> getProjectiles() = 0;

protected:
	void tryFire(float dt);
	void tryAscend(float dt);
	void checkDive(float dt);
	void tryDive(float dt);
	void setBerserkModeOn() { in_berserk_mode = true; }

	AscendDir ascend_direction;
	sf::Vector2f init_pos;
	sf::Vector2f target_pos;
	std::unordered_map<std::string, Animation*> animations;
	float max_health;
	float current_health;
	bool got_hit = false;
	bool should_die = false;
	bool should_fire = false;
	bool firing = false;
	float fire_tick;
	float fire_timer = 0.f;
	float fire_delay;
	float fire_delay_timer = 0.f;
	float ascend_time = 2.5f;
	float ascend_timer = 0.f;
	int fire_chance = 15;
	sf::Vector2f ascending_velocity;
	bool is_ascending = true;
	float ascend_delay = 0.f;
	float ascend_delay_timer = 0.f;
	bool in_berserk_mode = false;
	float diving_tick;
	float diving_timer = 0.f;
	float diving_time_max = 2.f;
	float diving_time = 0.f;
	int dive_chance = 15;
	int dive_sign;
	bool is_diving = false;

private:
	void setInitPos(AscendDir dir);
};

