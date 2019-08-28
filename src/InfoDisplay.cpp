#include "..\inc\InfoDisplay.h"

InfoDisplay::InfoDisplay() : heart(ResourceManager::get().textures.get("pickups"), sf::IntRect(100, 0, 14, 13))
{
	fonts.push_back(ResourceManager::get().fonts.get("VCR_OSD_MONO_1.001"));
	addPickupInfo();
	addInfo();
}

void InfoDisplay::updateInfo(const Player& player)
{
	lives_left = player.lives - 1;
	std::string reloadTime = std::to_string(player.reloadTime);
	reloadTime = reloadTime.substr(0, 4);

	std::string base_text[] =
	{   "LIVES LEFT: ",
		"SHIP SPEED: ",
		"MAG SIZE: ",
		"RELOAD TIME: ",
		"BULLET SPEED: ",
		"BULLET DAMAGE: ",
		"KILLS: ",
		"SCORE: ",
		" +5% SHIP SPEED", 
		" +1 MAG SIZE", 
		" +5% BULLET SPEED", 
		" -0.02s RELOAD TIME", 
		" +10% BULLET DAMAGE", 
		" +1 LIFE", 
		" WEAPON UPGRADE", 
		" WEAPON DOWNGRADE",
		" SHIELD (3s)",
		" CHAINING (3s)",
		"LCTRL - SHOOT",
		"<- -> - MOVE"};

	std::string dynamic_text[] = 
	{	"", 
		std::to_string(int(player.speedMod * 100.f + 1)) + "%",
		std::to_string(player.magazineSize),
		reloadTime + "s", 
		std::to_string(int(player.bulletSpeedMod * 100.f + 1)) + "%",
		std::to_string(int(player.dmgMod * 100.f)) + "%",
		std::to_string(player.getKills()),
		std::to_string(player.getScore()) };

	auto len1 = stats.size();
	for (unsigned i = 0; i < len1; i++)
		stats[i].setString(base_text[i] + dynamic_text[i]);

	auto len2 = pickup_info.size();
	for (unsigned i = 0; i < len2; i++)
		pickup_info[i].setString(base_text[len1 + i]);

	for (unsigned i = 0; i < 2; i++)
		controls[i].setString(base_text[len1 + len2 + i]);
}

void InfoDisplay::draw(sf::RenderWindow& w)
{
	unsigned len = stats.size();
	for (unsigned i = 0; i < len; i++)
		w.draw(stats[i]);

	len = pickup_info.size();
	for (unsigned i = 0; i < len; i++)
		w.draw(pickup_info[i]);
	
	len = lives_left;
	heart.setPosition({ 105.f, 303.f });
	for (unsigned i = 0; i < len; i++)
	{
		w.draw(heart);
		heart.move({ 16.f, 0.f });
	}

	len = pickup_sprites.size();
	for (unsigned i = 0; i < len; i++)
		w.draw(pickup_sprites[i]);

	for (unsigned i = 0; i < 2; i++)
		w.draw(controls[i]);
}

void InfoDisplay::addInfo()
{
	sf::Text t;
	t.setFont(fonts[0]);
	t.setFillColor(sf::Color::White);
	t.setCharacterSize(14);
	// Stats
	float pos_x = 10.f;
	float pos_y = 300.f;
	for (unsigned i = 0; i < 6; i++)
	{
		t.setPosition({ pos_x, pos_y });
		stats.push_back(t);
		pos_y += 25.f;
	}
	// Kills
	t.setPosition(10.f, 740.f); 
	t.setCharacterSize(18);
	stats.push_back(t);
	// Score
	t.setPosition(600.f, 2.f);  
	t.setCharacterSize(18);
	stats.push_back(t);
	// Pickups info
	t.setCharacterSize(12);
	unsigned len = pickup_sprites.size();
	pos_x = 1225.f;
	pos_y = 12.f;
	for (unsigned i = 0; i < len; i++)
	{
		t.setPosition({ pos_x, pos_y });
		pickup_info.push_back(t);
		pos_y += 30.f;
	}
	// Controls
	t.setCharacterSize(14);
	pos_x = 10.f;
	pos_y = 10.f;
	for (unsigned i = 0; i < 2; i++)
	{
		t.setPosition({ pos_x, pos_y });
		controls.push_back(t);
		pos_y += 25.f;
	}
}

void InfoDisplay::addPickupInfo()
{
	sf::Sprite s(ResourceManager::get().textures.get("pickups"));
	float pos_x = 1205.f;
	float pos_y = 10.f;
	for (unsigned i = 0; i < total_sprites; i++)
	{
		s.setTextureRect(sf::IntRect((i % 5) * 20, (i / 5) * 20, 20, 20));
		s.setPosition({ pos_x, pos_y });
		pickup_sprites.push_back(s);
		pos_y += 30.f;
	}
}
