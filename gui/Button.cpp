#include "Button.hpp"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& pos) : Box(size, pos)
{

}

void Button::update(sf::RenderWindow& w)
{
	if (isActive(w))
	{
		if (!was_active)
			setToActive();
	}
	else if (was_active)
		setToIdle();
}

bool Button::isActive(sf::RenderWindow& w)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(w);
	return box.getGlobalBounds().contains({ float(mouse_pos.x), float(mouse_pos.y) });
}

bool Button::isClicked(sf::RenderWindow& w)
{
	if (isActive(w) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void Button::setToIdle()
{
	was_active = false;
	if (!is_texture_set)
		updateMainColor(main_idle);

	updateOutlineColor(outline_idle);
	updateTextColor(text_idle);
}

void Button::setToActive()
{
	was_active = true;
	if (!is_texture_set)
		updateMainColor(main_active);

	updateOutlineColor(outline_active);
	updateTextColor(text_active);
}
