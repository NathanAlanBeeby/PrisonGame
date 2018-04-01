#pragma once
#include <SFML\Graphics.hpp>
#define Options_item_Number 4


class OptionsMenu
{
public:
	OptionsMenu(float width, float height);
	~OptionsMenu();

	void draw(sf::RenderWindow &window);
	void Up();
	void Down();
	void drawBars(sf::RenderWindow &window);
	int GetPressedItem() { return selectedItemIndex; }
	float Music = 50.0f;
	float Sound = 50.0f;

	void keyHandler();
	void mouseHandler(sf::RenderWindow &window);
	void instructionsPressed();
	void backPressed();
	bool instrucPress = false;
	bool backPress = false;

	sf::RectangleShape emptyMusic, emptySound;
	sf::RectangleShape MusicBar, SoundBar;


private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text OptionsMenuText[Options_item_Number];
};

