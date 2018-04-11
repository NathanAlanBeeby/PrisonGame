#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "guardDialogue.h"
#include "HUD.h"
#define prisoner_item_Number 3
enum prisonerDialogueState { prisonerTalk, prisonerMissions, prisonerTrade, prisonerDialogueMenu, prisonerNoState };
class prisonerDialogue
{

public:

	std::vector<bool> acceptedMission;
	std::vector <std::string> PM;


	prisonerDialogue();
	~prisonerDialogue();
	bool dialogueCheck = false;

	sf::RectangleShape DialogueBox, segBox;
	guardDialogue guardD;
	prisonerDialogueState prisonerDState;

	void drawDialogueBox(sf::View &view, sf::RenderWindow &window);
	void draw(sf::View &view, sf::RenderWindow &window);

	void Up();
	void Down();
	int GetPressedItem() { return prisonItemIndex; }

	sf::Texture tradeTexture, tradeButtonTexture, acceptTexture, declineTexture, cancelTexture;
	sf::RectangleShape tradeBox, tradeSymbol, tradeButton, acceptButton, declineButton, cancelButton;

	void Talk(sf::View &view, sf::RenderWindow &window);
	void Trade(sf::View &view, sf::RenderWindow &window);
	void Mission(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void dialogueHandler(sf::View &view, sf::RenderWindow &window, HUD &hud);


	sf::Text TalkDialogue, missionDialogue;
	int talkInt, missionsInt;


	std::vector<sf::Text>  missions;







private:
	int prisonItemIndex;
	sf::Font font;
	sf::Text PrisonerText[prisoner_item_Number];
};

