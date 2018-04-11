#include "Menu.h"
#include <iostream>


Menu::Menu(float width, float height)
{

	if (!font.loadFromFile("../assets/text_assets/FontFile.ttf"))
	{
		// error...
		//	std::cout << "Error loading file" << std::endl;
		system("pause");
	}

	MenuText[0].setFont(font);
	MenuText[0].setCharacterSize(100);
	MenuText[0].setFillColor(sf::Color::Blue);
	MenuText[0].setString("Play");
	MenuText[0].setPosition(sf::Vector2f(width / 2.3, height / (item_Number + 2) * 1)); // center item for width, have the amount of string items + 1, so that they're equally spaced out



	MenuText[1].setFont(font);
	MenuText[1].setCharacterSize(100);
	MenuText[1].setFillColor(sf::Color::White);
	MenuText[1].setString("Options");
	MenuText[1].setPosition(sf::Vector2f(width / 2.3, height / (item_Number + 2) * 2)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	MenuText[2].setFont(font);
	MenuText[2].setCharacterSize(100);
	MenuText[2].setFillColor(sf::Color::White);
	MenuText[2].setString("Exit");
	MenuText[2].setPosition(sf::Vector2f(width / 2.3, height / (item_Number + 2) * 3)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	selectedItemIndex = 0;
}

void Menu::MouseHandler(sf::RenderWindow &window) {
	sf::Vector2i mousePos = ::sf::Mouse::getPosition(window); // getting the position of the mouse relative to the window
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // left mouse button
		if (mousePos.x >= MenuText[0].getPosition().x && mousePos.x <= MenuText[0].getPosition().x + 80) { // if the x position is on the first HUD button
			if (mousePos.y >= MenuText[0].getPosition().y && mousePos.y <= MenuText[0].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "Play Button pressed" << std::endl;
				playPressed = true;
			}
		}
		if (mousePos.x >= MenuText[1].getPosition().x && mousePos.x <= MenuText[1].getPosition().x + 130) { // if the x position is on the first HUD button
			if (mousePos.y >= MenuText[1].getPosition().y && mousePos.y <= MenuText[1].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "Options Button pressed" << std::endl;
				optionsPressed = true;
			}
		}
		if (mousePos.x >= MenuText[2].getPosition().x && mousePos.x <= MenuText[2].getPosition().x + 100) { // if the x position is on the first HUD button
			if (mousePos.y >= MenuText[2].getPosition().y && mousePos.y <= MenuText[2].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "Exit Button pressed" << std::endl;
				exitPressed = true;
			}
		}
	}

}

void Menu::KeyHandler() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Up();
		std::cout << "Up pressed" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		Down();
		std::cout << "Down pressed" << std::endl;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		std::cout << "return pressed" << std::endl;
		switch (GetPressedItem()) {
		case 0: std::cout << "play pressed" << std::endl;
			playPressed = true;
			break;
		case 1: std::cout << "options pressed" << std::endl;
			optionsPressed = true;
			break;
		case 2: std::cout << "exit pressed" << std::endl;
			exitPressed = true;
			break;
		}
	}
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < item_Number; i++) {
		window.draw(MenuText[i]);
	}



}

void Menu::Up() {
	if (selectedItemIndex - 1 >= 0) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		MenuText[selectedItemIndex].setFillColor(sf::Color::White); //set the blue color to white
		selectedItemIndex--; //decrememnt the index
		MenuText[selectedItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}

void Menu::Down() {
	if (selectedItemIndex + 1 < item_Number) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		MenuText[selectedItemIndex].setFillColor(sf::Color::White); //set the blue color to white
		selectedItemIndex++; // increment the index
		MenuText[selectedItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}