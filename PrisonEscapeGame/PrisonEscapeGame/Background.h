#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Background // change this into an animated background for the menu
{
public:
	Background() {

	}

	Background(std::string image) { // gets the image
		if (!backgroundTexture.loadFromFile(image)) // if the image cannot be loaded
			std::cerr << "Error";
		std::cout << "Couldn't get background texture" << std::endl; // erroring out that the background texture couldn't be loaded in
		backgroundSprite.setTexture(backgroundTexture); // setting the texture to a sprite
	}

	void drawBackground(sf::RenderWindow &window) { //drawing the background sprite to the window
		window.draw(backgroundSprite);
	}


private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
};
