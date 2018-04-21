#include "GameOver.h"



GameOver::GameOver()
{
	//set the background, draw it out
	if (!GameOverBackground.loadFromFile("../assets/image_assets/GameOver.png")) {
		std::cout << "Cannot find gameover texture" << std::endl;
		system("pause");
	}
	if (!font.loadFromFile("../assets/text_assets/FontFile.ttf"))
	{
		system("pause");
	}
	ExitMenuText[0].setFont(font);
	ExitMenuText[0].setCharacterSize(100);
	ExitMenuText[0].setFillColor(sf::Color::Blue);
	ExitMenuText[0].setString("Retry");


	ExitMenuText[1].setFont(font);
	ExitMenuText[1].setCharacterSize(100);
	ExitMenuText[1].setFillColor(sf::Color::White);
	ExitMenuText[1].setString("Exit");

	selectedItemIndex = 0;


}


GameOver::~GameOver()
{
}


void GameOver::Up() {
	if (selectedItemIndex - 1 >= 0) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		ExitMenuText[selectedItemIndex].setFillColor(sf::Color::White); //set the blue color to white
		selectedItemIndex--; //decrememnt the index
		ExitMenuText[selectedItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}
void GameOver::Down() {
	if (selectedItemIndex + 1 < GameOver_Number) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		ExitMenuText[selectedItemIndex].setFillColor(sf::Color::White); //set the blue color to white
		selectedItemIndex++; // increment the index
		ExitMenuText[selectedItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}

void GameOver::drawEndScreen(sf::RenderWindow &window, sf::View &view) {
	BackgroundShape.setOrigin(400, 300); // Half Extents of swcreen
	BackgroundShape.setSize(sf::Vector2f(800, 600));
	BackgroundShape.setTexture(&GameOverBackground);
	BackgroundShape.setPosition(view.getCenter().x, view.getCenter().y); // positioning the shape to the centre of the view

	gameOverMessage.setFont(font);
	gameOverMessage.setString("Game Over!");
	gameOverMessage.setCharacterSize(100);
	gameOverMessage.setFillColor(sf::Color(255, 0, 0));
	gameOverMessage.setPosition(view.getCenter().x - 75, view.getCenter().y - 280);

	ExitMenuText[0].setPosition(sf::Vector2f(view.getCenter().x - 30, view.getCenter().y - 150)); // center item for width, have the amount of string items + 1, so that they're equally spaced out
	ExitMenuText[1].setPosition(sf::Vector2f(view.getCenter().x - 30, view.getCenter().y + 25)); // center item for width, have the amount of string items + 1, so that they're equally spaced out


	window.draw(BackgroundShape); // drawing the background image
	window.draw(gameOverMessage); // drawing the title
	for (int i = 0; i < GameOver_Number; i++) { // drawing the selectable button
		window.draw(ExitMenuText[i]);
	}

}

void GameOver::MouseHandler(sf::RenderWindow &window) {
	//ISSUE HERE IS THAT VIEW HAS MOVED
	sf::Vector2i mousePos = sf::Mouse::getPosition(window); // getting the position of the mouse relative to the window
	std::cout << "Mouse Pos - X: " << mousePos.x << ", Y: " << mousePos.y << std::endl;
	std::cout << "ExitMenuText 0 Pos - X: " << ExitMenuText[0].getPosition().x << ", Y: " << ExitMenuText[0].getPosition().y << std::endl;
	std::cout << "ExitMenuText 1 Pos - X: " << ExitMenuText[1].getPosition().x << ", Y: " << ExitMenuText[1].getPosition().y << std::endl;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // left mouse button
		if (mousePos.x >= ExitMenuText[0].getPosition().x && mousePos.x <= ExitMenuText[0].getPosition().x + 115) { // if the x position is on the first HUD button
			if (mousePos.y >= ExitMenuText[0].getPosition().y && mousePos.y <= ExitMenuText[0].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "rety Button pressed" << std::endl;
				

			}
		}
		if (mousePos.x >= ExitMenuText[1].getPosition().x && mousePos.x <= ExitMenuText[1].getPosition().x + 115) { // if the x position is on the first HUD button
			if (mousePos.y >= ExitMenuText[1].getPosition().y && mousePos.y <= ExitMenuText[1].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "exit Button pressed" << std::endl;
				exit(0); // exiting out 
				system("Exit");

			}
		}
	}
}


void GameOver::KeyHandler() {
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
		case 0: std::cout << "Retry pressed" << std::endl;
			//retry here - reset the game and replay
			break;
		case 1: std::cout << "Exit pressed" << std::endl;
			exit(0); // exiting out 
			system("Exit");
			break;
		}
	}
}