#include "Dummy.hpp"

Dummy::Dummy(std::string tex, sf::IntRect rect, int type, sf::Vector2f pos)
{
	sprite.setTexture(ResourceManager::get().textures.get(tex));
	sprite.setTextureRect(rect);
	sprite.setOrigin({ (float)rect.width / 2.f, (float)rect.height / 2.f });
	sprite.setPosition(pos);
	arrow.setTexture(ResourceManager::get().textures.get("util"));
	arrow.setTextureRect({ 14, 0, 10, 12 });
	arrow.setOrigin({ 5.f, 6.f });
	arrow.setRotation(direction * 45.f + 180.f);
	arrow.setPosition({ sprite.getPosition().x, sprite.getPosition().y - 30.f });
	this->tex = tex;
	this->rect = rect;
	this->type = type;
}

Dummy::Dummy(Dummy* d) : Dummy(d->tex, d->rect, d->type, { d->getPosition().x - 30.f, d->getPosition().y - 30.f })
{
	direction = d->direction;
	arrow.setRotation(float(direction) * 45.f + 180);
	delay = d->delay;
}

bool Dummy::isActive(sf::RenderWindow& w)
{
	if (!is_active)
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(w);
		if (sprite.getGlobalBounds().contains({ float(mouse_pos.x), float(mouse_pos.y) }) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			is_active = true;
			return true;
		}
		return false;
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return true;
		else
		{
			is_active = false;
			return false;
		}
	}
}

bool Dummy::isHovered(sf::RenderWindow& w)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(w);
	return sprite.getGlobalBounds().contains({ float(mouse_pos.x), float(mouse_pos.y) });
}

void Dummy::addDirection()
{
	direction++;
	if (direction > 7)
		direction = 0;
	arrow.setRotation(float(direction) * 45.f + 180.f);
}
