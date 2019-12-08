#pragma once
#include "StateManager.hpp"
#include "../entities/Projectile.hpp"
#include "../util/Background.hpp"
#include "../util/Random.hpp"
#include "../weapons/OneShot.hpp"
#include "../entities/aliens/Alien01.hpp"
#include "../effects/ParticleExplosion.hpp"
#include "../effects/Explosion.hpp"
#include "../util/SoundMaking.hpp"
#include "../entities/pickups/Health.hpp"
#include "../entities/pickups/Speed.hpp"
#include "../entities/pickups/Money.hpp"
#include "../entities/pickups/ReloadTime.hpp"
#include "../entities/pickups/FireRate.hpp"
#include "../entities/pickups/BulletSpeed.hpp"
#include "../entities/pickups/BulletCapacity.hpp"
#include "../util/levels/Level.hpp"
#include "../util/HUD.hpp"
#include "../states/Shop.hpp"
#include "../util/FloatingText.hpp"
#include "GameOver.hpp"

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
	std::vector<FloatingText*> floating_texts;

	Background* main_bg;
	Background* layer1;
	sf::Sprite sidebar_l;
	sf::Sprite sidebar_r;
	HUD* hud;
	Box* level_teller;
	Box* shop_teller;

	std::vector<ParticleExplosion*> particle_explosions;
	std::vector<Explosion*> sprite_explosions;

	bool is_game_over = false;
	bool gameover_loop = false;
	bool should_tell_level = true;
	bool should_tell_shop = false;
	bool shop_active = false;
	bool should_add_shop = false;
	bool shop_added = false;
	bool berserk_mode_activated = false;
	size_t active_level = 1;
	const size_t starting_level = 1;
	const size_t max_levels = 10;
private:
	void mapUpdates(float dt);
	void playerUpdates(float dt);
	void alienUpdates(float dt);
	void effectUpdates(float dt);
	void backgroundUpdates(float dt);
	void pickupUpdates(float dt);
	void floatingTextUpdates(float dt);
	void levelTellerUpdate(float dt);
	void shopTellerUpdate(float dt);

	void tryAddingPickup(sf::Vector2f pos);

	void tryStartingNewLevel();
};

