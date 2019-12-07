#include "ValuesBar.hpp"

ValuesBar::ValuesBar(float min, float max, std::string tex, sf::IntRect rect, sf::Vector2f pos)
{
	this->min = min;
	this->max = max;
	this->rect = rect;
	
	bar = new sf::Sprite(ResourceManager::get().textures.get(tex));
	bar->setPosition(pos);
	background.setFillColor(sf::Color::Black);
	background.setOutlineColor(sf::Color::White);
	background.setOutlineThickness(1.f);
	background.setSize({ float(rect.width), float(rect.height) });
	background.setPosition(pos);
}

ValuesBar::~ValuesBar()
{
	delete bar;
}

void ValuesBar::update(float current)
{
	bar->setTextureRect({ rect.left, rect.top, int((current - min) / (max - min) * rect.width), rect.height });
}

void ValuesBar::draw(sf::RenderWindow& w)
{
	w.draw(background);
	w.draw(*bar);
}
