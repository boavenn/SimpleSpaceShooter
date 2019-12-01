#include "LevelEditor.hpp"

LevelEditor::LevelEditor(sf::RenderWindow& w, StateManager& sm) : State(w, sm)
{
	main_bg = new Background(0.06f, { 171.f, 0 }, "background");
	layer1 = new Background(0.04f, { 171.f, 0 }, "layer1");

	dummies.push_back(new Dummy("aliens", { 0, 0, 50, 50 }, 1, { 50.f, 50.f }));
	dummies.push_back(new Dummy("aliens", { 0, 50, 50, 50 }, 2, { 100.f, 50.f }));
	dummies.push_back(new Dummy("aliens", { 0, 100, 50, 50 }, 3, { 50.f, 100.f }));
	dummies.push_back(new Dummy("aliens", { 0, 150, 50, 50 }, 4, { 100.f, 100.f }));
	dummies.push_back(new Dummy("aliens", { 0, 200, 50, 50 }, 5, { 50.f, 150.f }));

	for (int i = 2; i <= 14; i++)
	{
		lines.push_back(new sf::RectangleShape({ 1.f, (float)WindowProperties::getHeight() }));
		lines.back()->setPosition({ WindowProperties::getWidth() * (float)i / 16.f, 0 });
		lines.back()->setFillColor(sf::Color(255, 255, 255, 120));
		lines.push_back(new sf::RectangleShape({ (float)WindowProperties::getWidth(), 1.f }));
		lines.back()->setPosition({ 0, WindowProperties::getHeight() * (float)i / 16.f });
		lines.back()->setFillColor(sf::Color(255, 255, 255, 120));
	}

	lines.push_back(new sf::RectangleShape({ 1.f, (float)WindowProperties::getHeight() }));
	lines.back()->setPosition({ WindowProperties::getWidth() / 2.f, 0 });
	lines.back()->setFillColor(sf::Color(255, 0, 0));
	lines.push_back(new sf::RectangleShape({ (float)WindowProperties::getWidth(), 1.f }));
	lines.back()->setPosition({ 0, WindowProperties::getHeight() / 2.f });
	lines.back()->setFillColor(sf::Color(255, 0, 0));

	dir_setter = new InputButton({ 40.f, 20.f }, { 0.f, 0.f });
	dir_setter->setFont("VCR_OSD_MONO_1.001");
	dir_setter->setMainIdleColor(sf::Color::Black);
	dir_setter->setOutlineIdleColor(sf::Color::White);
	dir_setter->setTextIdleColor(sf::Color::White);
	dir_setter->setTextActiveColor(sf::Color::White);

	saver = new InputButton({ 300.f, 30.f }, { WindowProperties::getWidth() / 2.f, WindowProperties::getHeight() / 2.f });
	saver->setFont("VCR_OSD_MONO_1.001");
	saver->setMainIdleColor(sf::Color::Black);
	saver->setOutlineIdleColor(sf::Color::White);
	saver->setTextIdleColor(sf::Color::White);
	saver->setTextActiveColor(sf::Color::White);
}

LevelEditor::~LevelEditor()
{
	delete main_bg;
	delete layer1;
	delete dir_setter;
	delete saver;
}

void LevelEditor::update(float dt, sf::Event e)
{
	if (dir_setter_visible)
		dir_setter->checkUserInput(dt, e);
	if (saver_visible)
		saver->checkUserInput(dt, e);
	checkInput(dt, e);
	main_bg->update(dt);
	layer1->update(dt);

	if (should_pop)
		state_manager.popState();
}

void LevelEditor::draw()
{
	main_bg->draw(window);
	layer1->draw(window);
	for (Dummy* d : dummies)
		d->draw(window);
	for (sf::RectangleShape* l : lines)
		window.draw(*l);

	if (dir_setter_visible)
		dir_setter->draw(window);
	if (saver_visible)
		saver->draw(window);
}

void LevelEditor::checkInput(float dt, sf::Event e)
{
	if (!saving)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			saving = true;
			saver_visible = true;
			saver->isInputActive() = true;
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (active_dummy && dir_setter->isInputActive())
			{
				active_dummy->setDirection(std::atoi(dir_setter->getInput().c_str()));
			}

			dir_setter_visible = false;
			dir_setter->isInputActive() = false;
			dir_setter->resetInput();
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dir_setter->isInputActive())
		{
			active_dummy = nullptr;
			copy_active = false;
			delete_active = false;
		}

		if (!active_dummy)
		{
			for (Dummy* d : dummies)
			{
				if (d->isActive(window))
				{
					active_dummy = d;
					break;
				}
			}
		}

		if (active_dummy)
		{
			active_dummy->setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				dir_setter->setPosition(active_dummy->getPosition());
				dir_setter->isInputActive() = true;
				dir_setter_visible = true;
			}

			if (!copy_active && sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				copy_active = true;
				dummies.push_back(new Dummy(active_dummy));
			}

			if (!delete_active && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				for (size_t i = 0; i < dummies.size(); i++)
				{
					if (dummies[i] == active_dummy)
					{
						delete_active = true;
						delete active_dummy;
						active_dummy = nullptr;
						dummies.erase(dummies.begin() + i);
						break;
					}
				}
			}
		}
	}
	else
	{
		if (!saver->isInputActive())
		{
			saveToFile(saver->getInput());
			should_pop = true;
		}
	}
}

void LevelEditor::saveToFile(std::string filename)
{
	std::ofstream file("LevelConfig/" + filename + ".txt");
	if (file.is_open())
	{
		for (Dummy* d : dummies)
		{
			file << d->type << "|" << d->direction << "|" << d->getPosition().x << "|" << d->getPosition().y << "\n";
		}
		file.close();
	}
}
