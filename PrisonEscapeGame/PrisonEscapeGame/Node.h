#pragma once
#include "SFML\Graphics.hpp"
class Node {
public:
	void setPosition(sf::Vector2i tile) {
		x = tile.x;
		y = tile.y;
	};

	float x;
	float y;
	float g;
	float h;
	float f;
	bool passable = true;
};