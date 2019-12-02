#include "HUD.hpp"

HUD::HUD(Player* player)
{
	this->player = player;
	init_boxes();
	init_bars();

	float px = 0.f;
	for (int i = 0; i < player->getLivesMax(); i++, px += 16.f)
	{
		lives.push_back(new sf::Sprite(ResourceManager::get().textures.get("util"), { 0, 0, 14, 14 }));
		lives.back()->setPosition({ player->getPosition().x + 25.f + px, player->getPosition().y + 20.f });
	}
}

HUD::~HUD()
{

}

void HUD::update(float dt)
{
	money->setText(std::to_string(player->getMoney()) + "$");

	reload_time->update(player->getReloadTime());
	fire_rate->update(player->getShotGap());
	speed->update(player->getSpeed());

	float px = 0.f;
	for (int i = 0; i < player->getLivesMax(); i++, px += 16.f)
		lives[i]->setPosition({ player->getPosition().x + 25.f + px, player->getPosition().y + 20.f });
}

void HUD::draw(sf::RenderWindow& w)
{
	money->draw(w);

	for (int i = 0; i < player->getLivesLeft(); i++)
		w.draw(*lives[i]);

	reload_time->draw(w);
	w.draw(*R);
	fire_rate->draw(w);
	w.draw(*F);
	speed->draw(w);
	w.draw(*S);
	w.draw(*level);
}

void HUD::setLevel(int level)
{
	this->level->setString("Level: " + std::to_string(level));
}

void HUD::init_boxes()
{
	float px = 70.f;
	float py = 20.f;
	
	money = new Box({ 100.f, 50.f }, { px, py });
	money->setFont("MonospaceTypewriter");
	money->setText(std::to_string(player->getMoney()) + "$");
	money->setTextIdleColor(sf::Color::White);
	money->setTextScale({ 0.5f, 0.5f });
	money->centerText();

	level = new sf::Text("Level: 1", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	level->setCharacterSize(14);
	level->setPosition({ 40.f, 738.f });
}

void HUD::init_bars()
{
	reload_time = new ValuesBar(player->getReloadTime(), player->getReloadTimeMin(), "util", { 0, 16, 100, 14 }, {35.f, 100.f});
	R = new sf::Text("R", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	R->setCharacterSize(14);
	R->setPosition({ 15.f, 98.f });

	fire_rate = new ValuesBar(player->getShotGap(), player->getShotGapMin(), "util", { 0, 32, 100, 14 }, { 35.f, 120.f });
	F = new sf::Text("F", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	F->setCharacterSize(14);
	F->setPosition({ 15.f, 118.f });

	speed = new ValuesBar(player->getSpeed(), player->getSpeedMax(), "util", { 0, 46, 100, 14 }, { 35.f, 140.f });
	S = new sf::Text("S", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	S->setCharacterSize(14);
	S->setPosition({ 15.f, 138.f });
}
