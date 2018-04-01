#pragma once
#include <SFML/Graphics.hpp>
#define item_Number 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void Up();
	void Down();
	int GetPressedItem() { return selectedItemIndex; }
	void MouseHandler(sf::RenderWindow &window);
	void KeyHandler();
	bool playPressed = false;
	bool optionsPressed = false;
	bool exitPressed = false;

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text MenuText[item_Number];
};

