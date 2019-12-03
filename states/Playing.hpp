#pragma once
#include "StateManager.hpp"
#include "../entities/Projectile.hpp"
#include "../util/Background.hpp"
#include "../util/Random.hpp"
#include "../weapons/OneShot.hpp"
#include "../entities/aliens/Alien1.hpp"
#include "../effects/ParticleExplosion.hpp"
#include "../effects/Explosion.hpp"
#include "../util/SoundMaking.hpp"
#include "../entities/pickups/Health.hpp"
#include "../entities/pickups/Speed.hpp"
#include "../entities/pickups/Money.hpp"
#include "../entities/pickups/ReloadTime.hpp"
#include "../entities/pickups/FireRate.hpp"
#include "../util/levels/Level.hpp"
#include "../util/HUD.hpp"

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

	std::vector<Level*> levels;

	std::vector<Alien*> aliens;
	std::vector<Projectile*> alien_projectiles;
	std::vector<Pickup*> pickups;

	Background* main_bg;
	Background* layer1;
	sf::Sprite sidebar_l;
	sf::Sprite sidebar_r;
	HUD* hud;

	std::vector<ParticleExplosion*> particle_explosions;
	std::vector<Explosion*> sprite_explosions;

	bool is_game_over = false;
	size_t active_level = 1;
private:
	void mapUpdates(float dt);
	void playerUpdates(float dt);
	void alienUpdates(float dt);
	void effectUpdates(float dt);
	void backgroundUpdates(float dt);
	void pickupUpdates(float dt);

	void tryAddingPickup(sf::Vector2f pos);

	void tryStartingNewLevel();
};

