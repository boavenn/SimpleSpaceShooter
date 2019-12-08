#include "GameOver.hpp"
#include "Playing.hpp"

GameOver::GameOver(sf::RenderWindow& w, StateManager& sm, long score) : State(w, sm)
{
	this->score = score;

	gameover.setFont(ResourceManager::get().fonts.get("MonospaceTypewriter"));
	gameover.setString("GAME OVER");
	gameover.setFillColor(sf::Color::Red);
	gameover.setPosition({ float(WindowProperties::getWidth()) / 2.f - gameover.getGlobalBounds().width / 2.f, float(WindowProperties::getHeight()) / 2.f - 55.f });

	enter_name = new Box({ 200.f, 35.f }, { float(WindowProperties::getWidth()) / 2.f, float(WindowProperties::getHeight()) / 2.f });
	enter_name->setFont("MonospaceTypewriter");
	enter_name->setText("Enter your nickname");
	enter_name->setTextScale({ 0.7f, 0.7f });
	enter_name->centerText();
	enter_name->setTextIdleColor(sf::Color::White);
	enter_name->setMainIdleColor(sf::Color::Transparent);

	nickname_box = new InputButton({ 200.f, 50.f }, { float(WindowProperties::getWidth()) / 2.f, float(WindowProperties::getHeight()) / 2.f + 45.f });
	nickname_box->setFont("MonospaceTypewriter");
	nickname_box->setTextScale({ 0.5, 0.5 });
	nickname_box->setTextIdleColor(sf::Color::White);
	nickname_box->setTextActiveColor(sf::Color::White);
	nickname_box->setTexture("buttons");
	nickname_box->setTextureRect({ 0, 0, 200, 50 });
}

GameOver::~GameOver()
{
	delete enter_name;
	delete nickname_box;
}

void GameOver::update(float dt, sf::Event e)
{
	checkInput(dt, e);
	nickname_box->update(window);
	nickname_box->checkUserInput(dt, e);

	if (isConcurrent())
		state_manager.getPrevious(place_on_stack).update(dt, e);

	if (should_pop)
	{
		addScoreToFile();
		state_manager.popState(2);
	}
}

void GameOver::draw()
{
	if (isConcurrent())
		state_manager.getPrevious(place_on_stack).draw();

	window.draw(background);
	window.draw(gameover);
	enter_name->draw(window);
	nickname_box->draw(window);
}

void GameOver::checkInput(float dt, sf::Event e)
{
	if (isAbleToInput(dt))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			should_pop = true;

		if (nickname_box->isClicked(window))
			nickname_box->isInputActive() = true;
	}
}

void GameOver::addScoreToFile()
{
	if (!nickname_box->getInput().empty())
	{
		std::ofstream highscores("Highscores/highscores.txt", std::ios::app);
		highscores << score << "," << nickname_box->getInput() << ",";
		highscores.close();
	}
}
