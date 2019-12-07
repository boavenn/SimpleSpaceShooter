#include "HighScores.hpp"

HighScores::HighScores(sf::RenderWindow& w, StateManager& sm) : State(w, sm)
{
	float py = 100.f;
	for (size_t i = 0; i < 8; i++, py += 55.f)
	{
		scores_b.push_back(new Box({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f + 105.f, py }));
		scores_b.back()->setFont("MonospaceTypewriter");
		scores_b.back()->setTextScale({ 0.5f, 0.5f });
		scores_b.back()->setTextIdleColor(sf::Color::White);
		scores_b.back()->setMainIdleColor(sf::Color::White);
		scores_b.back()->setTexture("buttons");
		scores_b.back()->setTextureRect({ 0, 0, 200, 50 });

		names_b.push_back(new Box({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f - 105.f, py }));
		names_b.back()->setFont("MonospaceTypewriter");
		names_b.back()->setTextScale({ 0.5f, 0.5f });
		names_b.back()->setTextIdleColor(sf::Color::White);
		names_b.back()->setMainIdleColor(sf::Color::White);
		names_b.back()->setTexture("buttons");
		names_b.back()->setTextureRect({ 0, 0, 200, 50 });
	}

	quit = new Button({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f, 600.f });
	quit->setTexture("buttons");
	quit->setTextureRect({ 0, 0, 200, 50 });
	quit->setFont("MonospaceTypewriter");
	quit->setText("GO BACK");
	quit->setTextScale({ 0.5f, 0.5f });
	quit->addAnimation("idle", 0.2f);
	quit->getAnimationOf("idle").addFrame({ 0, 0, 200, 50 });
	quit->addAnimation("active", 0.05f);
	for (int i = 0; i < 10; i++)
		quit->getAnimationOf("active").addFrame({ 0, 50 + 50 * i, 200, 50 });
	quit->setTextIdleColor(sf::Color::White);
	quit->setMainIdleColor(sf::Color::White);
	quit->setTextActiveColor(sf::Color(94, 255, 209));
	quit->centerText();

	loadScores();
	sortScores();
	putScoresInBoxes();
}

HighScores::~HighScores()
{
	for (size_t i = 0; i < scores_b.size();)
	{
		delete scores_b.front();
		scores_b.erase(scores_b.begin());
	}

	for (size_t i = 0; i < names_b.size();)
	{
		delete names_b.front();
		names_b.erase(names_b.begin());
	}

	delete quit;
}

void HighScores::update(float dt, sf::Event e)
{
	checkInput(dt, e);

	quit->update(window);
	if (quit->isActive(window))
	{
		if (quit->getAnimationOf("active").isAnimationEnded())
			quit->setTextureRect(quit->getAnimationOf("active").getLastFrame());
		else
			quit->updateAnimation("active", dt);
	}
	else
	{
		quit->setTextureRect(quit->getAnimationOf("idle").getFirstFrame());
		quit->getAnimationOf("active").resetAnimation();
	}

	if (should_pop)
		state_manager.popState();
}

void HighScores::draw()
{
	for (auto& x : scores_b)
		x->draw(window);
	for (auto& x : names_b)
		x->draw(window);
	quit->draw(window);
}

void HighScores::checkInput(float dt, sf::Event e)
{
	if (isAbleToInput(dt))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			should_pop = true;

		if (quit->isClicked(window))
			should_pop = true;
	}
}

void HighScores::loadScores()
{
	std::ifstream highscores("Highscores/highscores.txt");
	if (highscores.good())
	{
		std::string line;
		std::string name;
		int points;
		int x = 0;
		while (std::getline(highscores, line, ','))
		{
			if (x++ % 2 == 0)
				points = std::stoi(line);
			else
			{
				name = line;
				scores.emplace_back(std::make_pair(points, name));
			}
		}
		highscores.close();
	}
}

void HighScores::sortScores()
{
	std::sort(scores.begin(), scores.end(), [](std::pair<int, std::string>& a, std::pair<int, std::string>& b) {return a.first > b.first; });
}

void HighScores::putScoresInBoxes()
{
	for (size_t i = 0; i < scores.size(); i++)
	{
		names_b[i]->setText(scores[i].second);
		names_b[i]->adjustTextToLeft(15.f);
		scores_b[i]->setText(std::to_string(scores[i].first));
		scores_b[i]->adjustTextToRight(15.f);
		if (i >= 7)
			break;
	}
}