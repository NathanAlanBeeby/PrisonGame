#pragma once
#include <SFML/Graphics.hpp>
#define Instructions_item_Number 6
class Instructions
{
public:
	Instructions(float width, float height);
	~Instructions();

	void draw(sf::RenderWindow &window);
	void Up();
	void Down();
	int GetPressedItem() { return selectedItemIndex; }
	void keyHandler();
	void mouseHandler(sf::RenderWindow &window);
	void backPressed();
	bool backPress = false;
	bool nextPress = false;

	void KeysSubMenu(sf::RenderWindow &window);
	void CraftingSubMenu(sf::RenderWindow &window);
	void SkillsSubMenu(sf::RenderWindow &window);
	void RoutineSubMenu(sf::RenderWindow &window);


	sf::Texture keysTexture, rotuineTexture;
	sf::RectangleShape keyBox, routinesBox;
	sf::Font keyFont;

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text InstructionsMenuText[Instructions_item_Number];
};

