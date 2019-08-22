#include "..\inc\Explosion.h"

Explosion::Explosion(sf::Vector2f pos) : explosion(sf::IntRect(0, 0, 40, 40), 23, 0.05f, 0)
{
	sprite.setTexture(ResourceManager::get().textures.get("explosion"));
	sprite.setOrigin({ 20.f,20.f });
	sprite.setPosition(pos);
	sprite.setScale({ 1.5f,1.5f });
}

void Explosion::update(float deltaTime)
{
	sprite.setTextureRect(explosion.update(deltaTime));
}

void Explosion::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}
