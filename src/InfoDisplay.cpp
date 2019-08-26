#include "..\inc\InfoDisplay.h"

InfoDisplay::InfoDisplay() : heart(ResourceManager::get().textures.get("pickups"), sf::IntRect(100, 0, 14, 13))
{
	fonts.push_back(ResourceManager::get().fonts.get("VCR_OSD_MONO_1.001"));
	addInfo();
}

void InfoDisplay::updateInfo(const Player& player)
{
	lives_left = player.lives - 1;
	infos[0].setString("LIVES LEFT: ");
	infos[1].setString("SHIP SPEED: " + std::to_string(int(player.speedMod * 100.f + 1)) + "%");
	infos[2].setString("MAG SIZE: " + std::to_string(player.magazineSize));
	std::string reloadTime = std::to_string(player.reloadTime);
	reloadTime = reloadTime.substr(0, 4);
	infos[3].setString("RELOAD TIME: " + reloadTime + "s");
	infos[4].setString("BULLET SPEED: " + std::to_string(int(player.bulletSpeedMod * 100.f + 1)) + "%");
	infos[5].setString("KILLS: " + std::to_string(player.getKills()));
	infos[6].setString("SCORE: " + std::to_string(player.getScore()));
}

void InfoDisplay::draw(sf::RenderWindow& w)
{
	unsigned len = infos.size();
	for (unsigned i = 0; i < len; i++)
		w.draw(infos[i]);
	
	len = lives_left;
	heart.setPosition({ 105.f, 303.f });
	for (unsigned i = 0; i < len; i++)
	{
		w.draw(heart);
		heart.move({ 16.f, 0.f });
	}
}

void InfoDisplay::addInfo() // Maybe I should try to do it better
{
	sf::Text t;
	t.setFont(fonts[0]);
	t.setFillColor(sf::Color::White);
	t.setCharacterSize(14);

	// Lives
	t.setPosition(10.f, 300.f); 
	infos.push_back(t);
	// Ship speed
	t.setPosition(10.f, 325.f);
	infos.push_back(t);
	// Mag size
	t.setPosition(10.f, 350.f); 
	infos.push_back(t);
	// Reload time
	t.setPosition(10.f, 375.f); 
	infos.push_back(t);
	// Bullet speed
	t.setPosition(10.f, 400.f);
	infos.push_back(t);
	// Kills
	t.setPosition(10.f, 700.f); 
	t.setCharacterSize(18);
	infos.push_back(t);
	// Score
	t.setPosition(600.f, 2.f);  
	t.setCharacterSize(18);
	infos.push_back(t);
}
