#include "Player.hpp"

Player::Player()
{
	sprite.setTexture(ResourceManager::get().textures.get("player"));
	sprite.setOrigin({ 35.f, 35.f });
	sprite.setPosition({ 683, 731 });

	Animation* animation = new Animation(0.5f);
	for(int i = 0; i < 4; i++)
		animation->addFrame({ 70 * i, 0, 70, 70 });
	animations.insert(std::make_pair("Stationary", animation));
}

void Player::input()
{
}

void Player::update(float deltaTime)
{
	sprite.setTextureRect(animations.at("Stationary")->update(deltaTime));
}

void Player::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}
