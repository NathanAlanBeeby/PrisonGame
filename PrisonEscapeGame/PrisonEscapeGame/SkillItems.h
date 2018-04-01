#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "HUD.h"
class SkillItems
{
public:
	SkillItems(std::string skillsFile, sf::RenderWindow &window);
	~SkillItems();
	std::vector<sf::RectangleShape>  skillItems;
	std::vector<sf::Texture>  SkillItemTexture;

	float skillItemX, skillItemY; // position X and Y

	void knowledgeIncrease(sf::RenderWindow &window, sf::View &view, HUD &hud);
	void strengthIncrease(sf::RenderWindow &window, sf::View &view, HUD &hud);
	void staminaIncrease(sf::RenderWindow &window, sf::View &view, HUD &hud);

	void drawSkillItems(sf::RenderWindow &window);
};

