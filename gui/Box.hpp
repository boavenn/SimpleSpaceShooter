#pragma once
#include "../res/ResourceManager.hpp"
#include "../util/Animation.hpp"

class Box
{
public:
	Box(const sf::Vector2f& size, const sf::Vector2f& pos);
	~Box();

	void draw(sf::RenderWindow& w);
	void updateAnimation(const std::string& str, float dt);

	void setMainIdleColor(const sf::Color& c);
	void setMainActiveColor(const sf::Color& c);
	void setOutlineIdleColor(const sf::Color& c);
	void setOutlineActiveColor(const sf::Color& c);
	void setTextIdleColor(const sf::Color& c);
	void setTextActiveColor(const sf::Color& c);
	void setFont(const std::string& font_name);
	void setText(const std::string& str, float spacing = 1.5f);
	void setTexture(const std::string& tex_name);
	void setTextureRect(const sf::IntRect& rect);
	void setPosition(sf::Vector2f pos) { box.setPosition(pos); centerText(); }
	void addAnimation(const std::string& name, float delay);
	void centerText();
	void adjustTextToLeft(float offset);
	void adjustTextToRight(float offset);

	const sf::Vector2f& getSize();
	const sf::Vector2f& getPosition();
	Animation& getAnimationOf(const std::string& str);

protected:
	void updateMainColor(const sf::Color& c);
	void updateOutlineColor(const sf::Color& c, float thickness = 2.f);
	void updateTextColor(const sf::Color& c);

	sf::RectangleShape box;
	sf::Font font;
	sf::Text text;
	sf::Color main_idle, main_active;
	sf::Color outline_idle, outline_active;
	sf::Color text_idle, text_active;
	std::unordered_map<std::string, Animation*> animation;
	bool is_texture_set = false;
	bool is_animation_set = false;
};

