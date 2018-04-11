#pragma once
#include "SFML\Graphics.hpp"
class Node {
public:
	void setPosition(sf::Vector2i tile) { // function to return tile position
		x = tile.x;
		y = tile.y;
	};

	float x; // position x
	float y; // position y
	float g; // goal node
	float h;
	float f;
	bool passable = true; // boolean value for if the tile is traversable
};