#pragma once

#include <SFML/Graphics.hpp>
#include "HUD.h"
#define skill_item_Number 7

class SkillMenu
{
public:
	SkillMenu(float width, float height);
	~SkillMenu();

	void drawBars(sf::RenderWindow &window, HUD &hud);
	void draw(sf::RenderWindow &window);
	void Up();
	void Down();
	int GetPressedItem() { return selectedItemIndex; }

	void keyHandler(HUD &hud);
	void mouseHandler(sf::RenderWindow &window);
	bool exitPress = false;
	bool gamePress = false;

	void gamePressed();
	void exitPressed();


	int startSkillPoints = 10;

	sf::Text SpendPoints;

	sf::RectangleShape StrBar, StaBar, EnduranceBar, ChaBar, KnoBar;
	sf::RectangleShape Str, Sta, Endurance, Cha, Kno;

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text SkillMenuText[skill_item_Number];
};

