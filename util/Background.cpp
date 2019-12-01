#include "Background.hpp"

Background::Background(float switch_time, sf::Vector2f pos, std::string tex_name)
{
	sprite.setTexture(ResourceManager::get().textures.get(tex_name));
	sprite.setPosition(pos);
	this->switch_time = switch_time;
	x_size = sprite.getTextureRect().width;
	y_size = sprite.getTextureRect().height;
}

void Background::update(float dt)
{
	timer += dt;
	if (timer >= switch_time)
	{
		timer -= switch_time;
		if (shift++ == 768)
			shift = 0;

		sprite.setTextureRect(sf::IntRect(0, 0 - shift, -1 * x_size, y_size));
	}
}

void Background::draw(sf::RenderWindow& w)
{
	w.draw(sprite);
}
