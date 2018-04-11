#include "OptionsMenu.h"
#include <iostream>

OptionsMenu::OptionsMenu(float width, float height)
{
	//set the background, draw it out
	if (!font.loadFromFile("../assets/text_assets/FontFile.ttf"))
	{
		// error...
		//	std::cout << "Error loading file" << std::endl;
		system("pause");
	}

	OptionsMenuText[0].setFont(font);
	OptionsMenuText[0].setCharacterSize(100);
	OptionsMenuText[0].setFillColor(sf::Color::Blue);
	OptionsMenuText[0].setString("Sound");
	OptionsMenuText[0].setPosition(sf::Vector2f(130, 30)); // center item for width, have the amount of string items + 1, so that they're equally spaced out



	OptionsMenuText[1].setFont(font);
	OptionsMenuText[1].setCharacterSize(100);
	OptionsMenuText[1].setFillColor(sf::Color::White);
	OptionsMenuText[1].setString("Music");
	OptionsMenuText[1].setPosition(sf::Vector2f(130, 130)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	OptionsMenuText[2].setFont(font);
	OptionsMenuText[2].setCharacterSize(100);
	OptionsMenuText[2].setFillColor(sf::Color::White);
	OptionsMenuText[2].setString("Instructions");
	OptionsMenuText[2].setPosition(sf::Vector2f(width / 2.5, height / 2.5)); // center item for width, have the amount of string items + 1, so that they're equally spaced out


	OptionsMenuText[3].setFont(font);
	OptionsMenuText[3].setCharacterSize(100);
	OptionsMenuText[3].setFillColor(sf::Color::White);
	OptionsMenuText[3].setString("Back");
	OptionsMenuText[3].setPosition(sf::Vector2f(40, height - 120)); // center item for width, have the amount of string items + 1, so that they're equally spaced out


	selectedItemIndex = 0;
}


OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::keyHandler() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Up();
		std::cout << "Up Pressed" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		Down();
		std::cout << "Down Pressed" << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		std::cout << "Left Pressed" << std::endl;
		switch (GetPressedItem()) {

		case 0: std::cout << "Sound pressed" << std::endl;
			if (Sound != 0) {
				Sound--;
			}
			break;
		case 1: std::cout << "Music pressed" << std::endl;
			if (Music != 0) {

				Music--;
			}
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		std::cout << "Right Pressed" << std::endl;
		switch (GetPressedItem()) {

		case 0: std::cout << "Sound pressed" << std::endl;
			if (Sound <= 99) {
				Sound++;


			}
			break;
		case 1: std::cout << "Music pressed" << std::endl;
			if (Music <= 99) {
				Music++;

			}
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		std::cout << "Return Pressed" << std::endl;
		switch (GetPressedItem()) {
		case 2: std::cout << "Instructions" << std::endl;
			instructionsPressed();
			break;
		case 3: std::cout << "Back" << std::endl;
			backPressed();
			break;

		}
	}
}
void OptionsMenu::instructionsPressed() {
	instrucPress = true;
}
void OptionsMenu::backPressed() {
	backPress = true;
}

void OptionsMenu::mouseHandler(sf::RenderWindow &window) {
	sf::Vector2i mousePos = ::sf::Mouse::getPosition(window); // getting the position of the mouse relative to the window
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // left mouse button
		if (mousePos.x >= OptionsMenuText[2].getPosition().x && mousePos.x <= OptionsMenuText[2].getPosition().x + 130) { // if the x position is on the first HUD button
			if (mousePos.y >= OptionsMenuText[2].getPosition().y && mousePos.y <= OptionsMenuText[2].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "Instructions Button pressed" << std::endl;
				instructionsPressed();
			}
		}
		if (mousePos.x >= OptionsMenuText[3].getPosition().x && mousePos.x <= OptionsMenuText[3].getPosition().x + 100) { // if the x position is on the first HUD button
			if (mousePos.y >= OptionsMenuText[3].getPosition().y && mousePos.y <= OptionsMenuText[3].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "Back Button pressed" << std::endl;
				backPressed();
			}
		}
	}
}




void OptionsMenu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < Options_item_Number; i++) {
		window.draw(OptionsMenuText[i]);
	}



}

void OptionsMenu::drawBars(sf::RenderWindow &window) {
	emptyMusic.setSize(sf::Vector2f(200, 20));
	emptyMusic.setFillColor(sf::Color(255, 0, 0));
	emptyMusic.setOutlineThickness(2);
	emptyMusic.setOutlineColor(sf::Color(0, 0, 0));

	emptySound.setSize(sf::Vector2f(200, 20));
	emptySound.setFillColor(sf::Color(255, 0, 0));
	emptySound.setOutlineThickness(2);
	emptySound.setOutlineColor(sf::Color(0, 0, 0));

	MusicBar.setSize(sf::Vector2f((Music * 2), 20));
	MusicBar.setFillColor(sf::Color(0, 0, 255));
	MusicBar.setOutlineThickness(2);
	MusicBar.setOutlineColor(sf::Color(0, 0, 0));

	SoundBar.setSize(sf::Vector2f((Sound * 2), 20));
	SoundBar.setFillColor(sf::Color(0, 0, 255));
	SoundBar.setOutlineThickness(2);
	SoundBar.setOutlineColor(sf::Color(0, 0, 0));



	emptySound.setPosition(250, 100);
	emptyMusic.setPosition(250, 200);


	SoundBar.setPosition(emptySound.getPosition().x, emptySound.getPosition().y);
	MusicBar.setPosition(emptyMusic.getPosition().x, emptyMusic.getPosition().y);

	window.draw(emptyMusic);
	window.draw(emptySound);
	window.draw(MusicBar);
	window.draw(SoundBar);
}


void OptionsMenu::Up() {
	if (selectedItemIndex - 1 >= 0) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		OptionsMenuText[selectedItemIndex].setFillColor(sf::Color::White); //set the blue color to white
		selectedItemIndex--; //decrememnt the index
		OptionsMenuText[selectedItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}

void OptionsMenu::Down() {
	if (selectedItemIndex + 1 < Options_item_Number) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		OptionsMenuText[selectedItemIndex].setFillColor(sf::Color::White); //set the blue color to white
		selectedItemIndex++; // increment the index
		OptionsMenuText[selectedItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}