#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow& w, StateManager& sm) : State(w, sm)
{
	background.setTexture(ResourceManager::get().textures.get("menubg"));
	background.setPosition({ 0.f, 0.f });
	init_buttons();
}

MainMenu::~MainMenu()
{
	for (size_t i = 0; i < buttons.size();)
	{
		delete buttons[i];
		buttons.erase(buttons.begin());
	}
}

void MainMenu::update(float dt, sf::Event e)
{
	checkInput(dt, e);

	for (auto& x : buttons)
	{
		x->update(window);
		if (x->isActive(window))
		{
			if (!x->getAnimationOf("active").isAnimationEnded())		
				x->updateAnimation("active", dt);
			else
				x->setTextureRect(x->getAnimationOf("active").getLastFrame());
		}
		else
		{
			x->setTextureRect(x->getAnimationOf("idle").getFirstFrame());
			x->getAnimationOf("active").resetAnimation();
		}
	}

	if (should_pop)
		state_manager.popState();
}

void MainMenu::draw()
{
	window.draw(background);
	for (auto& x : buttons)
		x->draw(window);
}

void MainMenu::checkInput(float dt, sf::Event e)
{
	if (isAbleToInput(dt))
	{
		if (buttons[0]->isClicked(window))
		{
			state_manager.pushState(std::make_unique<Playing>(window, state_manager));
		}
		else if (buttons[1]->isClicked(window))
		{
			state_manager.pushState(std::make_unique<LevelEditor>(window, state_manager));
		}
		else if (buttons[2]->isClicked(window))
		{
			//state_manager.pushState(std::make_unique<HighScores>(window, state_manager));
		}
		else if (buttons[3]->isClicked(window))
			should_pop = true;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			input_ability = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			should_pop = true;
	}
}

void MainMenu::init_buttons()
{
	std::string texts[] =
	{
		"PLAY",
		"LEVEL EDITOR",
		"HIGHSCORES",
		"QUIT"
	};

	for (size_t i = 0; i < 4; i++)
	{
		buttons.push_back(new Button({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f, 300.f + 70.f * i }));
		buttons.back()->setTexture("buttons");
		buttons.back()->setMainIdleColor(sf::Color::White);
		buttons.back()->addAnimation("idle", 0.2f);
		buttons.back()->getAnimationOf("idle").addFrame({ 0, 0, 200, 50 });
		buttons.back()->addAnimation("active", 0.05f);
		for (int i = 0; i < 10; i++)
			buttons.back()->getAnimationOf("active").addFrame({ 0, 50 + 50 * i, 200, 50 });
		buttons.back()->setTextIdleColor(sf::Color::White);
		buttons.back()->setTextActiveColor(sf::Color(94, 255, 209));
		buttons.back()->setFont("MonospaceTypewriter");
		buttons.back()->setText(texts[i]);
		buttons.back()->centerText();
		buttons.back()->setTextScale({ 0.5f, 0.5f });
	}
}
