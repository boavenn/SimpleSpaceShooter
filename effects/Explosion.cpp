#include "Explosion.hpp"

Explosion::Explosion(sf::Vector2f pos, float max_life_time, int type, float scale) : Effect(pos, max_life_time)
{
	animation = new Animation(max_life_time / 64.f);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			animation->addFrame({ 64 * j, 64 * i, 64, 64 });

	sprite.setTexture(ResourceManager::get().textures.get("explosion" + std::to_string(type)));
	sprite.setTextureRect(animation->getFirstFrame());
	sprite.setOrigin({ animation->getFirstFrame().width / 2.f, animation->getFirstFrame().height / 2.f });
	sprite.setPosition(pos);
	sprite.setScale({ scale, scale });
}

void Explosion::update(float dt)
{
	sprite.setTextureRect(animation->update(dt));

	life_timer += dt;
	if (life_timer >= max_life_time)
		should_die = true;
}

void Explosion::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}
