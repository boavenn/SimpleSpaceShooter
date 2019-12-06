#include "Player.hpp"
#include "../states/Playing.hpp"

Player::Player()
{
	reload_time = reload_time_max;
	bullets_capacity = bullets_capacity_min;
	shot_gap = shot_gap_max;
	speed = speed_min;
	proj_speed = proj_speed_min;

	Animation* animation = new Animation(0.2f);
	for(int i = 0; i < 8; i++)
		animation->addFrame({ 70 * i, 0, 70, 70 });
	animations.insert(std::make_pair("Stationary", animation));

	animation = new Animation(0.2f);
	for (int i = 0; i < 8; i++)
		animation->addFrame({ 70 * i, 70, 70, 70 });
	animations.insert(std::make_pair("Immune", animation));

	sprite.setTexture(ResourceManager::get().textures.get("player"));
	sprite.setTextureRect(animations.at("Stationary")->getFirstFrame());
	sprite.setOrigin({ 35.f, 35.f });
	sprite.setPosition({ (float)WindowProperties::getWidth() / 2,(float)WindowProperties::getHeight() - 40 });

	weapons.push_back(new OneShot(this));
	weapons.push_back(new DoubleShot(this));
	weapons.push_back(new TripleShot(this));
	weapons.push_back(new QuadShot(this));
	weapons.push_back(new EnhancedTriple(this));
}

Player::~Player()
{
	stopAllSounds();
	if (!animations.empty())
		animations.clear();
}

void Player::update(float dt)
{
	is_firing = false;
	should_explode = false;

	if (is_immune || is_immune_on_death)
		sprite.setTextureRect(animations.at("Immune")->update(dt));
	else
		sprite.setTextureRect(animations.at("Stationary")->update(dt));

	checkInput();
	checkAbilityToFire(dt);
	checkReload(dt);
	checkImmunity(dt);
	checkInputBlock(dt);
	checkPosition();
	sprite.move(velocity * dt);

	if (Playing::should_pause_sounds)
		pauseAllSounds();
}

void Player::draw(sf::RenderWindow& w)
{
	if(!block_input)
		w.draw(sprite);
}

bool Player::gotHitBy(Projectile* proj)
{
	if (this->contains(proj))
	{
		if (!is_immune && !is_immune_on_death)
		{
			subLive();
			block_input = true;
			is_immune_on_death = true;
			should_explode = true;
		}
		return true;
	}
	return false;
}

void Player::checkInput()
{
	velocity.x = 0;

	if (!block_input)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x = -speed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity.x = speed;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			try_fire = true;
		}
	}
}

void Player::checkAbilityToFire(float dt)
{
	if(!(shot_timer >= shot_gap))
		shot_timer += dt;

	if (try_fire)
	{
		try_fire = false;
		if (bullets_ready > 0 && shot_timer >= shot_gap)
		{
			shot_timer -= shot_gap;
			is_firing = true;
			bullets_ready--;
		}
	}
}

void Player::checkReload(float dt)
{
	if (bullets_ready < bullets_capacity)
	{
		reload_timer += dt;
		if (reload_timer >= reload_time)
		{
			reload_timer -= reload_time;
			bullets_ready++;
		}
	}
}

void Player::checkImmunity(float dt)
{
	if (is_immune_on_death)
	{
		immunity_timer += dt;
		if (immunity_timer >= on_death_immunity_time)
		{
			immunity_timer = 0.f;
			is_immune_on_death = false;
		}
	}
}

void Player::checkInputBlock(float dt)
{
	if (block_input)
	{
		input_block_timer += dt;
		if (input_block_timer >= on_death_input_block_time)
		{
			block_input = false;
			input_block_timer = 0.f;
		}
	}
}

void Player::checkPosition()
{
	if (sprite.getPosition().x < 216.f)
		sprite.setPosition({ 216.f, sprite.getPosition().y });
	if (sprite.getPosition().x > 1150.f)
		sprite.setPosition({ 1150.f, sprite.getPosition().y });
}

void Player::addLive()
{
	if (lives_left < int(lives_max))
		lives_left++;
}

void Player::subLive()
{
	lives_left--;
	if (active_weapon > 0)
		active_weapon--;
	if (lives_left < 0)
		lost_all_lives = true;
}

void Player::addSpeed(float speed)
{
	this->speed += speed;
	if (this->speed >= speed_max)
		this->speed = speed_max;
}

void Player::addMoney(int amount)
{
	money += amount;
}

void Player::subMoney(int amount)
{
	money -= amount;
	if (money < 0)
		money = 0;
}

void Player::addScore(long amount)
{
	score += amount;
}

void Player::addBulletsCapacity()
{
	if (bullets_capacity < bullets_capacity_max)
		bullets_capacity++;
}

void Player::increaseFireRate(float amount)
{
	shot_gap -= amount;
	if (shot_gap < shot_gap_min)
		shot_gap = shot_gap_min;
}

void Player::increaseProjSpeed(float amount)
{
	proj_speed += amount;
	if (proj_speed > proj_speed_max)
		proj_speed = proj_speed_max;
}

void Player::decreaseReloadTime(float amount)
{
	reload_time -= amount;
	if (reload_time < reload_time_min)
		reload_time = reload_time_min;
}

void Player::setImmunity()
{
	if (is_immune)
		immunity_timer = 0.f;
	else
		is_immune = true;
}
