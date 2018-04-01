#include "SkillItems.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string skillsfilename = "file.txt";
int skillItemNumber;
std::stringstream Sss;
std::string Ss;
std::string skillItemPath;

std::string bikeStr = "bike";
std::string weightsStr = "weight";

SkillItems::SkillItems(std::string skillsFile, sf::RenderWindow &window)
{
	std::ifstream myInputFile;
	myInputFile.open(skillsFile, std::ios_base::in);
	if (myInputFile.is_open())
	{
		//read the first line which has the number of elements
		std::getline(myInputFile, Ss);
		Sss.str(Ss);
		Sss.ignore(22);
		Sss >> skillItemNumber;
		skillItems.resize(skillItemNumber);
		SkillItemTexture.resize(skillItemNumber);

		Sss.clear();


		float sizeX, sizeY;
		float rot; // rotation


		for (int i = 0; i < skillItemNumber; i++)
		{

			//NAME AND NUMBER
			getline(myInputFile, Ss);
			Sss.clear();
			Sss.str(Ss);
			//POSITION
			getline(myInputFile, Ss);
			Sss.clear();
			Sss.str(Ss);
			Sss >> skillItemX >> skillItemY;
			//SIZE
			getline(myInputFile, Ss);
			Sss.clear();
			Sss.str(Ss);
			Sss >> sizeX >> sizeY;
			//TEXTURE
			getline(myInputFile, Ss);
			Sss.clear();
			Sss.str(Ss);
			Sss >> skillItemPath;

			sf::Vector2i pos(skillItemX, skillItemY);
			sf::Vector2f size(sizeX, sizeY);


			if (!SkillItemTexture[i].loadFromFile(skillItemPath)) {
				std::cout << "Load fail Error on DoorsTexture" << std::endl;
				system("pause");
			}


			skillItems[i].setPosition(pos.x, pos.y);
			skillItems[i].setOrigin(size / 2.0f);
			skillItems[i].setSize(size);
			skillItems[i].setTexture(&SkillItemTexture[i]);
		}
	}
}


SkillItems::~SkillItems()
{
}

void SkillItems::drawSkillItems(sf::RenderWindow &window) {
	for (int i = 0; i < skillItems.size(); i++) {
		window.draw(skillItems[i]);
	}
}

void SkillItems::knowledgeIncrease(sf::RenderWindow &window, sf::View &view, HUD &hud) {
	sf::RectangleShape knowledgeWindow;
	knowledgeWindow.setSize(sf::Vector2f(250, 400));
	knowledgeWindow.setFillColor(sf::Color(242, 232, 171));
	knowledgeWindow.setOutlineThickness(2);
	knowledgeWindow.setOutlineColor(sf::Color(0, 0, 0));
	knowledgeWindow.setPosition(view.getCenter().x - 125, view.getCenter().y - 130);
	window.draw(knowledgeWindow);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && hud.playerKnowledge < 100) { hud.playerKnowledge += 1; }

}
void SkillItems::strengthIncrease(sf::RenderWindow &window, sf::View &view, HUD &hud) {
	sf::RectangleShape strengthWindow;
	strengthWindow.setSize(sf::Vector2f(250, 400));
	strengthWindow.setFillColor(sf::Color(242, 232, 171));
	strengthWindow.setOutlineThickness(2);
	strengthWindow.setOutlineColor(sf::Color(0, 0, 0));
	strengthWindow.setPosition(view.getCenter().x - 125, view.getCenter().y - 130);
	window.draw(strengthWindow);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && hud.playerStrength < 100) { hud.playerStrength += 1; }
}
void SkillItems::staminaIncrease(sf::RenderWindow &window, sf::View &view, HUD &hud) {
	sf::RectangleShape bikeWindow;
	bikeWindow.setSize(sf::Vector2f(250, 400));
	bikeWindow.setFillColor(sf::Color(242, 232, 171));
	bikeWindow.setOutlineThickness(2);
	bikeWindow.setOutlineColor(sf::Color(0, 0, 0));
	bikeWindow.setPosition(view.getCenter().x - 125, view.getCenter().y - 130);
	window.draw(bikeWindow);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && hud.playerStamina < 100) { hud.playerStamina += 1; }
}