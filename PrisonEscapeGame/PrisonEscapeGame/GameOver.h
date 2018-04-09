#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#define GameOver_Number 2
class GameOver // implementing this as a menu instead of an interface as I may want to add an SFML plug in for animation for the end game and parts of the game
{
public:
	GameOver();
	~GameOver();

	void Up();
	void Down();
	int GetPressedItem() { return selectedItemIndex; }
	void MouseHandler(sf::RenderWindow &window);
	void KeyHandler();
	void drawEndScreen(sf::RenderWindow &window, sf::View &view);
private:
	int selectedItemIndex;
	sf::Text gameOverMessage;
	sf::RectangleShape BackgroundShape;
	sf::Font font;
	sf::Texture GameOverBackground;
	sf::Text ExitMenuText[GameOver_Number];
};






