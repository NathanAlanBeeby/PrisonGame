#include "Instructions.h"
#include <iostream>

enum InstructionsState { noState, keysState, craftState, skillState, routineState };
InstructionsState state;
Instructions::Instructions(float width, float height)
{
	state = noState;
	//set the background, draw it out
	if (!font.loadFromFile("../assets/text_assets/FontFile.ttf"))
	{
		// error...
		//	std::cout << "Error loading file" << std::endl;
		system("pause");
	}

	InstructionsMenuText[0].setFont(font);
	InstructionsMenuText[0].setCharacterSize(100);
	InstructionsMenuText[0].setFillColor(sf::Color::Blue);
	InstructionsMenuText[0].setString("Keys");
	InstructionsMenuText[0].setPosition(sf::Vector2f(50, 20)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	InstructionsMenuText[1].setFont(font);
	InstructionsMenuText[1].setCharacterSize(100);
	InstructionsMenuText[1].setFillColor(sf::Color::White);
	InstructionsMenuText[1].setString("Crafting");
	InstructionsMenuText[1].setPosition(sf::Vector2f(50, 120)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	InstructionsMenuText[2].setFont(font);
	InstructionsMenuText[2].setCharacterSize(100);
	InstructionsMenuText[2].setFillColor(sf::Color::White);
	InstructionsMenuText[2].setString("Skills");
	InstructionsMenuText[2].setPosition(sf::Vector2f(50, 220)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	InstructionsMenuText[3].setFont(font);
	InstructionsMenuText[3].setCharacterSize(100);
	InstructionsMenuText[3].setFillColor(sf::Color::White);
	InstructionsMenuText[3].setString("Routine");
	InstructionsMenuText[3].setPosition(sf::Vector2f(50, 320)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	InstructionsMenuText[4].setFont(font);
	InstructionsMenuText[4].setCharacterSize(100);
	InstructionsMenuText[4].setFillColor(sf::Color::White);
	InstructionsMenuText[4].setString("Back");
	InstructionsMenuText[4].setPosition(sf::Vector2f(60, height - 120)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	InstructionsMenuText[5].setFont(font);
	InstructionsMenuText[5].setCharacterSize(100);
	InstructionsMenuText[5].setFillColor(sf::Color::White);
	InstructionsMenuText[5].setString("Next");
	InstructionsMenuText[5].setPosition(sf::Vector2f(width - 160, height - 120)); // center item for width, have the amount of string items + 1, so that they're equally spaced out

	selectedItemIndex = 0;
}


Instructions::~Instructions()
{
}

void Instructions::draw(sf::RenderWindow &window) {
	for (int i = 0; i < Instructions_item_Number; i++) {
		window.draw(InstructionsMenuText[i]);
	}
	if (state == keysState) { // drawing the menu's if the button is clicked and the state is changed
		KeysSubMenu(window);
	}
	if (state == craftState) {
		CraftingSubMenu(window);
	}
	if (state == skillState) {
		SkillsSubMenu(window);
	}
	if (state == routineState) {
		RoutineSubMenu(window);
	}
}

void Instructions::keyHandler(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Up();
		std::cout << "Up Pressed" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		Down();
		std::cout << "Down Pressed" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		std::cout << "Return Pressed" << std::endl;
		switch (GetPressedItem()) {
		case 0: std::cout << "Keys" << std::endl;
			state = keysState;
			
			break;
		case 1: std::cout << "Crafting" << std::endl;
			state = craftState;
			break;
		case 2: std::cout << "Skills" << std::endl;
			state = skillState;
			break;
		case 3: std::cout << "Routine" << std::endl;
			state = routineState;
			break;
		case 4: std::cout << "Back" << std::endl;
			backPressed();
			
			break;
		case 5: std::cout << "Next" << std::endl;
			//this can have functionality later when more information is needed to be inputted into the instructions menu
			break;
		}
	}
}

void Instructions::KeysSubMenu(sf::RenderWindow &window){
	std::cout << "Keys sub menu in action" << std::endl;
	if (!keysTexture.loadFromFile("../assets/image_assets/KeysMenu.png")) {
		std::cout << "Load fail Error on keysTexture" << std::endl;
		system("pause");
	}
	if (!keyFont.loadFromFile("../assets/text_assets/fontFile.ttf")) {
		std::cout << "Load fail Error on keyFont" << std::endl;
		system("pause");
	}
	keyBox.setTexture(&keysTexture);
	keyBox.setSize(sf::Vector2f(300, 700));
	keyBox.setPosition(window.getSize().x / 2 + 10, 20);
	window.draw(keyBox);
	std::vector<sf::Text> KeyInstruction;
	std::vector<sf::Text> first3Keys;
	KeyInstruction.resize(7);
	first3Keys.resize(3);

	first3Keys[0].setString("Movement Keys");
	first3Keys[1].setString("Selecting Item in menu");
	first3Keys[2].setString("Attack button");
	first3Keys[0].setPosition(window.getSize().x / 2 + 100, 45);
	first3Keys[1].setPosition(window.getSize().x / 2 + 100, 110);
	first3Keys[2].setPosition(window.getSize().x / 2 + 100, 170);

	for (int i = 0; i < first3Keys.size(); i++) {
		first3Keys[i].setFont(keyFont);
		first3Keys[i].setCharacterSize(40); // setting the character size
		first3Keys[i].setFillColor(sf::Color(0, 0, 0));
			window.draw(first3Keys[i]);
	}

	KeyInstruction[0].setString("access skills menu in game");
	KeyInstruction[1].setString("access inventory in game");
	KeyInstruction[2].setString("If instructions open, open craft menu");
	KeyInstruction[3].setString("acess missions menu in game");
	KeyInstruction[4].setString("access your reputation with factions");
	KeyInstruction[5].setString("action key - used to interact");
	KeyInstruction[6].setString("close dialogue key");

	for (int i = 0; i < KeyInstruction.size(); i++) {
		KeyInstruction[i].setFont(keyFont);
		KeyInstruction[i].setCharacterSize(40); // setting the character size
		KeyInstruction[i].setFillColor(sf::Color(0, 0, 0));
		KeyInstruction[i].setPosition(window.getSize().x / 2 + 100, window.getSize().y / 2 - 100 + (i * 40));
		window.draw(KeyInstruction[i]);
	}

}
void Instructions::CraftingSubMenu(sf::RenderWindow &window) {
	std::cout << "Crafting Sub Menu in action" << std::endl;
}
void Instructions::SkillsSubMenu(sf::RenderWindow &window) {
	std::cout << "SKills Sub Menu in action" << std::endl;

	if (!keyFont.loadFromFile("../assets/text_assets/fontFile.ttf")) {
		std::cout << "Load fail Error on keyFont" << std::endl;
		system("pause");
	}
	//skillBox.setTexture(&skillTexture);
	//skillBox.setSize(sf::Vector2f(300, 500));
	//skillBox.setPosition(window.getSize().x / 2 + 10, 30);
	//window.draw(skillBox);
	std::vector<sf::Text> skillsInstruction;
	std::vector<sf::Text> skillsTitle;
	skillsInstruction.resize(5);
	skillsTitle.resize(5);

	skillsTitle[0].setString("Strength");
	skillsTitle[1].setString("Stamina");
	skillsTitle[2].setString("Endurance");
	skillsTitle[3].setString("Charisma");
	skillsTitle[4].setString("Knowledge");

	skillsInstruction[0].setString("Gained from weights bench");
	skillsInstruction[1].setString("Gained From exercise bike");
	skillsInstruction[2].setString("Gained by fighting");
	skillsInstruction[3].setString("Gained by talking");
	skillsInstruction[4].setString("Gained by reading books");

	for (int i = 0; i < skillsTitle.size(); i++) {
		skillsTitle[i].setPosition(window.getSize().x / 2 + 130, 20 + (i * 80));
		skillsTitle[i].setFont(keyFont);
		skillsTitle[i].setCharacterSize(40);
		skillsTitle[i].setFillColor(sf::Color(255, 0, 255));
		window.draw(skillsTitle[i]);
	}
	for (int i = 0; i < skillsInstruction.size(); i++) {
		skillsInstruction[i].setPosition(window.getSize().x / 2 + 130, 50 + (i * 80));
		skillsInstruction[i].setFont(keyFont);
		skillsInstruction[i].setCharacterSize(40); 
		skillsInstruction[i].setFillColor(sf::Color(0, 0, 0));
		window.draw(skillsInstruction[i]);
	}

}
void Instructions::RoutineSubMenu(sf::RenderWindow &window) {
	std::cout << "Routines Sub menu in action" << std::endl;
	if (!rotuineTexture.loadFromFile("../assets/image_assets/routinesMenu.png")) {
		std::cout << "Load fail Error on routine Texture" << std::endl;
		system("pause");
	}
	if (!keyFont.loadFromFile("../assets/text_assets/fontFile.ttf")) {
		std::cout << "Load fail Error on keyFont" << std::endl;
		system("pause");
	}
	routinesBox.setTexture(&rotuineTexture);
	routinesBox.setSize(sf::Vector2f(300, 500));
	routinesBox.setPosition(window.getSize().x / 2 + 10, 30);
	window.draw(routinesBox);
	std::vector<sf::Text> routineInstruction;
	std::vector<sf::Text> routineSubText;
	routineInstruction.resize(5);
	routineSubText.resize(6);

	routineInstruction[0].setString("Bed Time");
	routineInstruction[1].setString("Chow Time");
	routineInstruction[2].setString("Shower Time");
	routineInstruction[3].setString("Yard Time");
	routineInstruction[4].setString("Work Time");


	routineInstruction[0].setPosition(window.getSize().x / 2 + 100, 45);
	routineInstruction[1].setPosition(window.getSize().x / 2 + 130, 125);
	routineInstruction[2].setPosition(window.getSize().x / 2 + 100, 220);
	routineInstruction[3].setPosition(window.getSize().x / 2 + 120, 320);
	routineInstruction[4].setPosition(window.getSize().x / 2 + 130, 400);


	for (int i = 0; i < routineInstruction.size(); i++) {
		routineInstruction[i].setFont(keyFont);
		routineInstruction[i].setCharacterSize(40); // setting the character size
		routineInstruction[i].setFillColor(sf::Color(0, 0, 0));
		window.draw(routineInstruction[i]);
	}

}

void Instructions::backPressed() {
	backPress = true;
}


void Instructions::mouseHandler(sf::RenderWindow &window){
	sf::Vector2i mousePos = ::sf::Mouse::getPosition(window); // getting the position of the mouse relative to the window
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // left mouse button
		if (mousePos.x >= InstructionsMenuText[4].getPosition().x && mousePos.x <= InstructionsMenuText[4].getPosition().x + 115) { // if the x position is on the first HUD button
			if (mousePos.y >= InstructionsMenuText[4].getPosition().y && mousePos.y <= InstructionsMenuText[4].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "Exit Button pressed" << std::endl;
				backPressed();

			}
		}
		if (mousePos.x >= InstructionsMenuText[5].getPosition().x && mousePos.x <= InstructionsMenuText[5].getPosition().x + 115) { // if the x position is on the first HUD button
			if (mousePos.y >= InstructionsMenuText[5].getPosition().y && mousePos.y <= InstructionsMenuText[5].getPosition().y + 100) { // if the y position is between the HUD button
				std::cout << "next Button pressed" << std::endl;
				nextPress = true;

			}
		}
	}
}




void Instructions::Up() {
	if (selectedItemIndex - 1 >= 0) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		InstructionsMenuText[selectedItemIndex].setFillColor(sf::Color::White); //set the blue color to white
		selectedItemIndex--; //decrememnt the index
		InstructionsMenuText[selectedItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}

void Instructions::Down() {
	if (selectedItemIndex + 1 < Instructions_item_Number) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		InstructionsMenuText[selectedItemIndex].setFillColor(sf::Color::White); //set the blue color to white
		selectedItemIndex++; // increment the index
		InstructionsMenuText[selectedItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}