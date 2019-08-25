#include "..\inc\InfoDisplay.h"

InfoDisplay::InfoDisplay()
{
	fonts.push_back(ResourceManager::get().fonts.get("VCR_OSD_MONO_1.001"));
	addInfo();
}

void InfoDisplay::updateInfo(const Player& player)
{
	infos[0].setString("LIVES LEFT: " + std::to_string(player.lives - 1));
	infos[1].setString("SHIP SPEED: " + std::to_string(int(player.speedMod * 100.f + 1)) + "%");
	infos[2].setString("MAG SIZE: " + std::to_string(player.magazineSize));
	std::string reloadTime = std::to_string(player.reloadTime);
	reloadTime = reloadTime.substr(0, 4);
	infos[3].setString("RELOAD TIME: " + reloadTime + "s");
	infos[4].setString("BULLET SPEED: " + std::to_string(int(player.bulletSpeedMod * 100.f + 1)) + "%");
}

void InfoDisplay::draw(sf::RenderWindow& w)
{
	unsigned len = infos.size();
	for (unsigned i = 0; i < len; i++)
		w.draw(infos[i]);
}

void InfoDisplay::addInfo()
{
	sf::Text t;
	t.setFont(fonts[0]);
	t.setFillColor(sf::Color::White);
	t.setCharacterSize(14);
	t.setPosition(10.f, 300.f);
	infos.push_back(t);
	t.setPosition(10.f, 325.f);
	infos.push_back(t);
	t.setPosition(10.f, 350.f);
	infos.push_back(t);
	t.setPosition(10.f, 375.f);
	infos.push_back(t);
	t.setPosition(10.f, 400.f);
	infos.push_back(t);
}
