#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "HUD.h"
#define guard_item_Number 3
enum guardDialogueState { guardTalk, guardMissions, snitching, guardDialogueMenu, guardNoState };
class guardDialogue
{

public:


	std::string GM1;
	std::string GM2;
	std::string GM3;
	std::string GM4;
	std::string GM5;
	std::string GM6;
	std::string GM7;


	guardDialogue();
	~guardDialogue();
	bool dialogueCheck = false;
	sf::RectangleShape DialogueBox, segBox;

	guardDialogueState guardDState;

	sf::Texture acceptTexture, declineTexture, cancelTexture;
	sf::RectangleShape acceptButton, declineButton, cancelButton;

	void drawDialogueBox(sf::View &view, sf::RenderWindow &window);
	void draw(sf::View &view, sf::RenderWindow &window);
	void Up();
	void Down();
	int GetPressedItem() { return guardItemIndex; }

	void Talk(sf::View &view, sf::RenderWindow &window);
	void Snitch(sf::View &view, sf::RenderWindow &window);
	void Mission(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void dialogueHandler(sf::View &view, sf::RenderWindow &window, HUD &hud);

	sf::Text TalkDialogue, missionDialogue;
	int talkInt, missionsInt;
	int prisonInfo = 0; // int for number of information collected on prisoner


private:
	int guardItemIndex;
	sf::Font font;
	sf::Text GuardText[guard_item_Number];
};

