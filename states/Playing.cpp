#include "Playing.hpp"

Playing::Playing(sf::RenderWindow& w, StateManager& sm) : State(w, sm)
{
	
}

Playing::~Playing()
{

}

void Playing::update(float dt, sf::Event e)
{
	player->update(dt);
}

void Playing::draw()
{
	player->draw(window);
}

void Playing::checkInput(float dt, sf::Event e)
{

}
