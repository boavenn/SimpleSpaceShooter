#include "Shop.hpp"

Shop::Shop(sf::RenderWindow& w, StateManager& sm, Player* player, int level) : State(w, sm)
{
	this->player = player;
	transition_freeze_time = 0.2f;
	hud = new HUD(player);
	hud->shouldDisplayLives(false);
	hud->setLevel(level);
	background.setTexture(ResourceManager::get().textures.get("shop"));
	background.setPosition({ 171.f, 0.f });
	sidebar_l.setTexture(ResourceManager::get().textures.get("sidebar"));
	sidebar_l.setPosition({ 0, 0 });
	sidebar_r.setTexture(ResourceManager::get().textures.get("sidebar"));
	sidebar_r.setTextureRect({ 171, 0, -171, 768 });
	sidebar_r.setPosition({ float(WindowProperties::getWidth() - 171), 0 });

	init_options();

	addSoundBuffer("shop");
	playSound("shop", 1.f, 100.f, true);
}

Shop::~Shop()
{
	delete hud;
	delete quit;
}

void Shop::update(float dt, sf::Event e)
{
	checkInput(dt, e);

	explosion_timer += dt;
	if (explosion_timer >= explosion_add_interval)
	{
		explosions.push_back(new ParticleExplosion({ R::nextFloat(200, 1166), R::nextFloat(0, 768) }, R::nextFloat(2, 4), 100));
		explosion_timer -= explosion_add_interval;
	}

	for (Button* b : options)	
		b->update(window);	
	quit->update(window);
	hud->update(dt);
	for (ParticleExplosion* p : explosions)
		p->update(dt);

	for (size_t i = 0; i < explosions.size(); i++)
	{
		if (explosions[i]->shouldDie())
		{
			delete explosions[i];
			explosions.erase(explosions.begin() + i);
			i--;
		}
	}

	if (should_pop)
		state_manager.popState();
}

void Shop::draw()
{
	window.draw(background);
	for (ParticleExplosion* p : explosions)
		p->draw(window);
	window.draw(sidebar_l);
	window.draw(sidebar_r);
	hud->draw(window);
	for (Button* b : options)
		b->draw(window);
	for (Box* b : price_boxes)
		b->draw(window);
	quit->draw(window);
}

void Shop::checkInput(float dt, sf::Event e)
{
	if (isAbleToInput(dt))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || quit->isClicked(window))
		{
			should_pop = true;
			stopAllSounds();
		}

		if (options[0]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[0]->getText()) && player->getLivesLeft() < player->getLivesMax())
			{
				player->addLive();
				player->subMoney(prices.at(options[0]->getText()));
				input_ability = false;
			}
		}
		else if (options[1]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[1]->getText()) && player->getBulletSpeed() < player->getBulletSpeedMax())
			{
				player->increaseProjSpeed(0.04f);
				player->subMoney(prices.at(options[1]->getText()));
				input_ability = false;
			}
		}
		else if (options[2]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[2]->getText()) && player->getBulletsCapacity() < player->getBulletsCapacityMax())
			{
				player->addBulletsCapacity();
				player->subMoney(prices.at(options[2]->getText()));
				input_ability = false;
			}
		}
		else if (options[3]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[3]->getText()) && player->getShotGap() > player->getShotGapMin())
			{
				player->increaseFireRate(0.0025f);
				player->subMoney(prices.at(options[3]->getText()));
				input_ability = false;
			}
		}
		else if (options[4]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[4]->getText()) && player->getReloadTime() > player->getReloadTimeMin())
			{
				player->decreaseReloadTime(0.005f);
				player->subMoney(prices.at(options[4]->getText()));
				input_ability = false;
			}
		}
		else if (options[5]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[5]->getText()) && player->getSpeed() < player->getSpeedMax())
			{
				player->addSpeed(2.5f);
				player->subMoney(prices.at(options[5]->getText()));
				input_ability = false;
			}
		}
		else if (options[6]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[6]->getText()) && player->getActiveWeapon() != 4)
			{
				player->setActiveWeapon(4);
				player->subMoney(prices.at(options[6]->getText()));
				input_ability = false;
			}
		}
		else if (options[7]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[7]->getText()) && player->getActiveWeapon() != 3)
			{
				player->setActiveWeapon(3);
				player->subMoney(prices.at(options[7]->getText()));
				input_ability = false;
			}
		}
		else if (options[8]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[8]->getText()) && player->getActiveWeapon() != 2)
			{
				player->setActiveWeapon(2);
				player->subMoney(prices.at(options[8]->getText()));
				input_ability = false;
			}
		}
		else if (options[9]->isClicked(window))
		{
			if (player->getMoney() >= prices.at(options[9]->getText()) && player->getActiveWeapon() != 1)
			{
				player->setActiveWeapon(1);
				player->subMoney(prices.at(options[9]->getText()));
				input_ability = false;
			}
		}
	}
}

void Shop::init_options()
{
	std::string names[] =
	{
		"Life",
		"Bullet speed",
		"More bullets",
		"Fire rate",
		"Reload time",
		"Ship speed",

		"Ultra triple",
		"Quad shot",
		"Triple shot",
		"Double shot"
	};

	prices.insert(std::make_pair("Life", 500));
	prices.insert(std::make_pair("Bullet speed", 300));
	prices.insert(std::make_pair("More bullets", 100));
	prices.insert(std::make_pair("Fire rate", 50));
	prices.insert(std::make_pair("Reload time", 35));
	prices.insert(std::make_pair("Ship speed", 20));

	prices.insert(std::make_pair("Ultra triple", 600));
	prices.insert(std::make_pair("Quad shot", 300));
	prices.insert(std::make_pair("Triple shot", 150));
	prices.insert(std::make_pair("Double shot", 50));

	float py = 200.f;
	for (int i = 0; i < util_quantity; i++)
	{
		options.push_back(new Button({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f - 350.f, py }));
		options.back()->setTexture("buttons");
		options.back()->setTextureRect({ 0, 0, 200, 50 });
		options.back()->setFont("MonospaceTypewriter");
		options.back()->setText(names[i]);
		options.back()->setTextIdleColor(sf::Color::White);
		options.back()->setTextActiveColor(sf::Color::Green);
		options.back()->setTextScale({ 0.5f, 0.5f });
		options.back()->adjustTextToLeft(15.f);

		price_boxes.push_back(new Box({ 100.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f - 200.f, py }));
		price_boxes.back()->setTexture("buttons");
		price_boxes.back()->setTextureRect({ 200, 0, 100, 50 });
		price_boxes.back()->setFont("MonospaceTypewriter");
		price_boxes.back()->setText(std::to_string(prices.at(names[i])) + "$");
		price_boxes.back()->setTextIdleColor(sf::Color::White);
		price_boxes.back()->setTextScale({ 0.5f, 0.5f });
		price_boxes.back()->adjustTextToRight(15.f);
		py += 50.f;
	}

	py = 200.f;
	for (int i = 0; i < weapon_quantity; i++)
	{
		options.push_back(new Button({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f + 250.f, py }));
		options.back()->setTexture("buttons");
		options.back()->setTextureRect({ 0, 0, 200, 50 });
		options.back()->setFont("MonospaceTypewriter");
		options.back()->setText(names[util_quantity + i]);
		options.back()->setTextIdleColor(sf::Color::White);
		options.back()->setTextActiveColor(sf::Color::Green);
		options.back()->setTextScale({ 0.5f, 0.5f });
		options.back()->adjustTextToLeft(15.f);

		price_boxes.push_back(new Box({ 100.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f + 400.f, py }));
		price_boxes.back()->setTexture("buttons");
		price_boxes.back()->setTextureRect({ 200, 0, 100, 50 });
		price_boxes.back()->setFont("MonospaceTypewriter");
		price_boxes.back()->setText(std::to_string(prices.at(names[util_quantity + i])) + "$");
		price_boxes.back()->setTextIdleColor(sf::Color::White);
		price_boxes.back()->setTextScale({ 0.5f, 0.5f });
		price_boxes.back()->adjustTextToRight(15.f);
		py += 50.f;
	}

	quit = new Button({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f, float(WindowProperties::getHeight() - 50.f) });
	quit->setTexture("buttons");
	quit->setTextureRect({ 0, 0, 200, 50 });
	quit->setFont("MonospaceTypewriter");
	quit->setText("QUIT SHOP");
	quit->setTextIdleColor(sf::Color::White);
	quit->setTextActiveColor(sf::Color::Green);
	quit->setTextScale({ 0.5f, 0.5f });
	quit->centerText();
}
