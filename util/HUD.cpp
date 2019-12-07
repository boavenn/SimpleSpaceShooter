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
	delete reload_time;
	delete speed;
	delete proj_speed;
	delete fire_rate;
	delete R;
	delete S;
	delete F;
	delete BS;
	delete level;
	delete money;
	delete score;
	for (size_t i = 0; i < lives.size();)
	{
		delete lives.front();
		lives.erase(lives.begin());
	}
}

void HUD::update(float dt)
{
	money->setText(std::to_string(player->getMoney()) + "$");
	money->centerText();
	score->setText("Score: " + std::to_string(player->getScore()));
	score->centerText();

	reload_time->update(player->getReloadTime());
	fire_rate->update(player->getShotGap());
	speed->update(player->getSpeed());
	proj_speed->update(player->getBulletSpeed());

	float px = 0.f;
	for (int i = 0; i < player->getLivesMax(); i++, px += 16.f)
		lives[i]->setPosition({ player->getPosition().x + 25.f + px, player->getPosition().y + 20.f });
}

void HUD::draw(sf::RenderWindow& w)
{
	money->draw(w);
	score->draw(w);

	if(should_display_lives)
		for (int i = 0; i < player->getLivesLeft(); i++)
			w.draw(*lives[i]);

	reload_time->draw(w);
	w.draw(*R);
	fire_rate->draw(w);
	w.draw(*F);
	speed->draw(w);
	w.draw(*S);
	proj_speed->draw(w);
	w.draw(*BS);
	w.draw(*level);
}

void HUD::setLevel(int level)
{
	this->level->setString("Level: " + std::to_string(level));
}

void HUD::init_boxes()
{
	float px = 80.f;
	float py = 20.f;
	
	money = new Box({ 100.f, 50.f }, { px, py });
	money->setFont("MonospaceTypewriter");
	money->setText(std::to_string(player->getMoney()) + "$");
	money->setTextIdleColor(sf::Color::White);
	money->setTextScale({ 0.5f, 0.5f });
	money->centerText();

	score = new Box({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f, 10.f });
	score->setFont("MonospaceTypewriter");
	score->setText("Score:  0");
	score->setTextIdleColor(sf::Color::White);
	score->setTextScale({ 0.4f, 0.4f });
	score->centerText();

	level = new sf::Text("Level: 1", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	level->setCharacterSize(14);
	level->setPosition({ 40.f, 738.f });
}

void HUD::init_bars()
{
	reload_time = new ValuesBar(player->getReloadTimeMax(), player->getReloadTimeMin(), "util", { 0, 14, 100, 14 }, {35.f, 100.f});
	R = new sf::Text("R", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	R->setCharacterSize(14);
	R->setPosition({ 15.f, 98.f });

	fire_rate = new ValuesBar(player->getShotGapMax(), player->getShotGapMin(), "util", { 0, 30, 100, 14 }, { 35.f, 120.f });
	F = new sf::Text("F", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	F->setCharacterSize(14);
	F->setPosition({ 15.f, 118.f });

	speed = new ValuesBar(player->getSpeedMin(), player->getSpeedMax(), "util", { 0, 46, 100, 14 }, { 35.f, 140.f });
	S = new sf::Text("S", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	S->setCharacterSize(14);
	S->setPosition({ 15.f, 138.f });

	proj_speed = new ValuesBar(player->getBulletSpeedMin(), player->getBulletSpeedMax(), "util", { 0, 62, 100, 14 }, { 35.f, 160.f });
	BS = new sf::Text("BS", ResourceManager::get().fonts.get("MonospaceTypewriter"));
	BS->setCharacterSize(14);
	BS->setPosition({ 10.f, 158.f });
}
