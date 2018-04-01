#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Background // change this into an animated background for the menu
{
public:
	Background() {

	}

	Background(std::string image) {
		if (!backgroundTexture.loadFromFile(image))
			std::cerr << "Error";
		backgroundSprite.setTexture(backgroundTexture);
	}

	void drawBackground(sf::RenderWindow &window) {
		window.draw(backgroundSprite);
	}


private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
};
