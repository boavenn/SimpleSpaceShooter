#include "Player.hpp"

Player::Player()
{
	sprite.setTexture(ResourceManager::get().textures.get("player"));
	sprite.setOrigin({ 35.f, 35.f });
	sprite.setPosition({ 683, 728 });

	Animation* animation = new Animation(0.5f);
	for(int i = 0; i < 4; i++)
		animation->addFrame({ 70 * i, 0, 70, 70 });
	animations.insert(std::make_pair("Stationary", animation));
}

Player::~Player()
{
	if (!animations.empty())
		animations.clear();
}

void Player::update(float dt)
{
	is_firing = false;
	sprite.setTextureRect(animations.at("Stationary")->update(dt));
	checkInput();
	checkAbilityToFire(dt);
	checkReload(dt);
	sprite.move(velocity * dt);
}

void Player::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}

void Player::checkInput()
{
	float speed = 300.f;
	velocity.x = 0;

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
