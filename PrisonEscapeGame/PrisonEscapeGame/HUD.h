#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

class HUD
{

public:

	
	std::vector<sf::RectangleShape> InvSlot;
	std::vector<sf::RectangleShape> EmptySlot;
	std::vector<sf::Texture> EmptyTexture;

	bool yardTime, chowTime, showerTime, workTime, freeTime, bedTime;

	std::vector<sf::Text> missions;


	int missionList;
	
	sf::CircleShape PlayerIcon;

	sf::RectangleShape clockOuterBox, clockDigital, date, routineBox;

	sf::RectangleShape PlayerBox, noHealth, health, noXP, XP, prisonPound, emptyGRep, emptyPRep, GRep, PRep;

	sf::RectangleShape box, box1, box2;

	sf::RectangleShape StrengthBar, StaminaBar, ArmourBar, CharismaBar, KnowledgeBar;

	sf::RectangleShape Strength, Stamina, Armour, Charisma, Knowledge;

	sf::RectangleShape MissionsBox, SkillsBox, InventoryBox, characterBox, CashBox;

	sf::RectangleShape CraftButton, CraftBox, closeCraft, craftInputBox, submitCraft;

	sf::Clock HUDClock;

	sf::Texture playerTexture, halfHealthPlayer, lowHealthPlayer, poundTexture;
	sf::Texture Skills, Inventory, Missions;
	sf::Texture characterTexture;
	sf::Font font, HUDFont, HUDFont2, RoutineFont;
	sf::Text playerMissions;

	bool MisOpen = false;
	bool SkilOpen = false;
	bool InvOpen = false;
	bool RepOpen = false;

	bool craftOpen = false;

	float healthBar = 210;
	float XPcount = 0;
	float HUDopacity = 150;

	float maxXP = 210; //create a system where the maxXP costs more each level of the players health
	int playerLevel = 1; // (maxXP * playerLevel) + or * someValue so that each level is harder than the last

	
	int MisOpenCount = 0; // way of knowing if the player has hit the key twice
	int InvOpenCount = 0; // way of knowing if the player has hit the key twice
	int SkilOpenCount = 0; // way of knowing if the player has hit the key twice
	int RepOpenCount = 0;
	int craftOpenCount = 0;
	


	int HUDTime = 0; // this will be the time for the screen
	int HUDTimeMinute = 0; // hudtime minutes
	int day = 0; // the day number
	
	int prisonMoney = 0; // the cash you start with


	int prisonerRep;
	int guardRep;

	float night = 100; // box hue


	int playerStrength = 0; // the stat number that will affect the skills bar
	int playerStamina = 0;
	int playerArmour = 0;
	int playerCharisma = 0;
	int playerKnowledge = 0; 

	
	
	HUD();

	void drawMissions(sf::View &view, sf::RenderWindow &window);
	void drawSkills(sf::View &view, sf::RenderWindow &window);
	void drawInventory(sf::View &view, sf::RenderWindow &window);
	void drawReputation(sf::View &view, sf::RenderWindow &window);
	void drawCraft(sf::View &view, sf::RenderWindow &window);
	void drawHUD(sf::View &view, sf::RenderWindow &window);
	void HUDUserInput(sf::View &view, sf::RenderWindow &window);
	void Times(sf::View &view, sf::RenderWindow &window);
	void MouseInput(sf::RenderWindow &window);

	void skillsOpening();
	void missionsOpening();
	void inventoryOpening();
	void craftingOpening();
	void craftButtonClicked();
	void reputationOpening();
	
};
