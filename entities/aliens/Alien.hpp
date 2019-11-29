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
	Alien(float max_health);
	~Alien();
	bool gotHitBy(Projectile* proj);
	bool shouldDie() { return should_die; }
	bool isFiring() { return firing; }
	virtual std::vector<Projectile*> getProjectiles() = 0;

protected:
	void tryFire(float dt);

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
	int fire_chance = 5;
};

