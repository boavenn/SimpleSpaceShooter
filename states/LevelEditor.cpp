#include "LevelEditor.hpp"
#include <sstream>

LevelEditor::LevelEditor(sf::RenderWindow& w, StateManager& sm) : State(w, sm)
{
	main_bg = new Background(0.06f, { 171.f, 0 }, "background");
	layer1 = new Background(0.04f, { 171.f, 0 }, "layer1");
	sidebar_l.setTexture(ResourceManager::get().textures.get("sidebar"));
	sidebar_l.setPosition({ 0, 0 });
	sidebar_r.setTexture(ResourceManager::get().textures.get("sidebar"));
	sidebar_r.setTextureRect({ 171, 0, -171, 768 });
	sidebar_r.setPosition({ float(WindowProperties::getWidth() - 171), 0 });

	init_dummies();
	init_lines();
	init_setters();
	init_instructions();
}

LevelEditor::~LevelEditor()
{
	delete main_bg;
	delete layer1;
	delete setter;
	delete saver;
	for (size_t i = 0; i < dummies.size(); i++)
	{
		delete dummies.front();
		dummies.erase(dummies.begin());
	}
	for (size_t i = 0; i < instructions.size(); i++)
	{
		delete instructions.front();
		instructions.erase(instructions.begin());
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		delete lines.front();
		lines.erase(lines.begin());
	}
}

void LevelEditor::update(float dt, sf::Event e)
{
	if (setter_visible)
		setter->checkUserInput(dt, e);
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
	for (sf::RectangleShape* l : lines)
		window.draw(*l);
	window.draw(sidebar_l);
	window.draw(sidebar_r);
	for (Dummy* d : dummies)
		d->draw(window);
	for (Box* b : instructions)
		b->draw(window);

	if (setter_visible)
		setter->draw(window);
	if (saver_visible)
		saver->draw(window);
}

void LevelEditor::checkInput(float dt, sf::Event e)
{
	if (!saving)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			should_pop = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			saving = true;
			saver_visible = true;
			saver->isInputActive() = true;
		}

		dir_change_timer += dt;
		if (dir_change_timer >= dir_change_gap)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				for (Dummy* d : dummies)
					if (d->isHovered(window))
						d->addDirection();
			}
			dir_change_timer -= dir_change_gap;
		}

		if (!setter->isInputActive())
		{
			if (active_dummy)
			{
				std::string input = setter->getInput();
				if (!input.empty())
				{
					std::stringstream ss(input);
					float delay;
					ss >> delay;
					active_dummy->setDelay(delay / 1000.f);
				}				
			}

			setter_visible = false;
			setter->resetInput();
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !setter->isInputActive())
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
			setter->setPosition(active_dummy->getPosition());

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				setter->isInputActive() = true;
				setter_visible = true;
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
			file << d->type << "|" << d->direction << "|" << d->delay << "|" << d->getPosition().x << "|" << d->getPosition().y << "\n";
		}
		file.close();
	}
}

void LevelEditor::init_lines()
{
	for (int i = WindowProperties::getWidth() / 2; i >= 0; i -= 50)
	{
		lines.push_back(new sf::RectangleShape({ 1.f, (float)WindowProperties::getHeight() }));
		lines.back()->setPosition({ WindowProperties::getWidth() * (float)i / 1366.f, 0 });
		lines.back()->setFillColor(sf::Color(255, 255, 255, 120));
	}

	for (int i = WindowProperties::getHeight() / 2; i >= 0; i -= 50)
	{
		lines.push_back(new sf::RectangleShape({ (float)WindowProperties::getWidth(), 1.f }));
		lines.back()->setPosition({ 0, WindowProperties::getHeight() * (float)i / 768.f });
		lines.back()->setFillColor(sf::Color(255, 255, 255, 120));
	}

	for (int i = WindowProperties::getWidth() / 2; i <= 1366; i += 50)
	{
		lines.push_back(new sf::RectangleShape({ 1.f, (float)WindowProperties::getHeight() }));
		lines.back()->setPosition({ WindowProperties::getWidth() * (float)i / 1366.f, 0 });
		lines.back()->setFillColor(sf::Color(255, 255, 255, 120));
	}

	for (int i = WindowProperties::getHeight() / 2; i <= 768; i += 50)
	{
		lines.push_back(new sf::RectangleShape({ (float)WindowProperties::getWidth(), 1.f }));
		lines.back()->setPosition({ 0, WindowProperties::getHeight() * (float)i / 768.f });
		lines.back()->setFillColor(sf::Color(255, 255, 255, 120));
	}

	lines.push_back(new sf::RectangleShape({ 1.f, (float)WindowProperties::getHeight() }));
	lines.back()->setPosition({ WindowProperties::getWidth() / 2.f, 0 });
	lines.back()->setFillColor(sf::Color(255, 0, 0));
	lines.push_back(new sf::RectangleShape({ (float)WindowProperties::getWidth(), 1.f }));
	lines.back()->setPosition({ 0, WindowProperties::getHeight() / 2.f });
	lines.back()->setFillColor(sf::Color(255, 0, 0));
}

void LevelEditor::init_dummies()
{
	dummies.push_back(new Dummy("aliens", { 0, 0, 50, 50 }, 1, { 50.f, 50.f }));
	dummies.push_back(new Dummy("aliens", { 0, 50, 50, 50 }, 2, { 100.f, 50.f }));
	dummies.push_back(new Dummy("aliens", { 0, 100, 50, 50 }, 3, { 50.f, 100.f }));
	dummies.push_back(new Dummy("aliens", { 0, 150, 50, 50 }, 4, { 100.f, 100.f }));
	dummies.push_back(new Dummy("aliens", { 0, 200, 50, 50 }, 5, { 50.f, 150.f }));
}

void LevelEditor::init_setters()
{
	setter = new InputButton({ 80.f, 15.f }, { 0.f, 0.f });
	setter->setFont("MonospaceTypewriter");
	setter->setMainIdleColor(sf::Color(240, 237, 238));
	setter->setOutlineIdleColor(sf::Color(39, 39, 39));
	setter->setTextIdleColor(sf::Color(39, 39, 39));
	setter->setTextActiveColor(sf::Color(39, 39, 39));

	saver = new InputButton({ 400.f, 45.f }, { WindowProperties::getWidth() / 2.f, WindowProperties::getHeight() / 2.f });
	saver->setFont("MonospaceTypewriter");
	saver->setMainIdleColor(sf::Color(240, 237, 238));
	saver->setOutlineIdleColor(sf::Color(39, 39, 39));
	saver->setTextIdleColor(sf::Color(39, 39, 39));
	saver->setTextActiveColor(sf::Color(39, 39, 39));
}

void LevelEditor::init_instructions()
{
	std::string instr[] =
	{
		"Pressing LMB on a dummy makes it active",
		"Press RMB to set ascend delay in milliseconds",
		"Press C to clone",
		"Press D to delete",
		"Press S to save in a file",
		"Press A to change ascending direction"
	};

	for (size_t i = 0; i < 6; i++)
	{
		instructions.push_back(new Box({ 200.f, 25.f }, { 261.f, 470.f + i * 50.f }));
		instructions.back()->setFont("MonospaceTypewriter");
		instructions.back()->setTextIdleColor(sf::Color::White);
		instructions.back()->setTextScale({ 1.2f, 1.2f });
		instructions.back()->setTextOutlineColor(sf::Color::Black);
		instructions.back()->setText(instr[i]);
		instructions.back()->adjustTextToLeft(15.f);
	}
}
