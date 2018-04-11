#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "HUD.h"
class InventoryItems
{
public:
	std::vector<sf::RectangleShape>  InvItems;
	std::vector<sf::Texture>  inventoryTexture;

	float InvX, InvY; // position X and Y
	InventoryItems(std::string inventoryFile, sf::RenderWindow &window);

	int inv2by2Size, inv5by2Size, inv4by4Size = 0;

	std::vector<sf::RectangleShape> Items2by2; // 4
	std::vector<sf::RectangleShape> Items5by2; // 10
	std::vector<sf::RectangleShape> Items4by4; // 16
	sf::RectangleShape item;






	void prepare2x2Items(sf::View &view);
	void prepare5x2Items(sf::View &view);
	void prepare4x4Items(sf::View &view);
	void draw2x2Items(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void draw5x2Items(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void draw4x4Items(sf::View &view, sf::RenderWindow &window, HUD &hud);


	~InventoryItems();
};

