#pragma once
#include "StateManager.hpp"
#include "../entities/Player.hpp"
#include "../entities/Projectile.hpp"
#include "../util/Background.hpp"
#include "../util/Random.hpp"
#include "../weapons/OneShot.hpp"
#include "../entities/aliens/Alien01.hpp"
#include "../effects/ParticleExplosion.hpp"
#include "../effects/Explosion.hpp"
#include "../util/SoundMaking.hpp"
#include "../entities/pickups/Health.hpp"

typedef Random R;

class Playing : public State, public SoundMaking
{
public:
	Playing(sf::RenderWindow& w, StateManager& sm);
	~Playing();
	void update(float dt, sf::Event e);
	void draw();
	void checkInput(float dt, sf::Event e);


	static bool should_pause_sounds;
private:

	Player* player = new Player();
	std::vector<Projectile*> player_projectiles;

	std::vector<Alien*> aliens;
	std::vector<Projectile*> alien_projectiles;
	std::vector<Pickup*> pickups;

	Background* main_bg;
	Background* layer1;

	std::vector<ParticleExplosion*> particle_explosions;
	std::vector<Explosion*> sprite_explosions;

private:
	void playerUpdates(float dt);
	void alienUpdates(float dt);
	void effectUpdates(float dt);
	void backgroundUpdates(float dt);
	void pickupUpdates(float dt);
};

