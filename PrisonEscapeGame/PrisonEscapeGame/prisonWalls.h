#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>


class prisonWalls
{
public:
	prisonWalls(std::string wallFile, sf::RenderWindow &window);
	sf::RectangleShape wallBlock;
	sf::Texture wallTexture;

	void drawWalls(sf::RenderWindow &window);
	std::vector<sf::RectangleShape>  Walls;

	sf::Vector2i pos;

	float x, y;



};

