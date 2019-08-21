#include "..\inc\ScreenManager.h"

ScreenManager::ScreenManager()
{

}

void ScreenManager::update(float deltaTime)
{
	player.update(deltaTime);
}

void ScreenManager::draw(sf::RenderWindow& w)
{
	player.draw(w);
}
