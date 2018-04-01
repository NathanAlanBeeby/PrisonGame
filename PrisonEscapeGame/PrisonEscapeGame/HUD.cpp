#include "HUD.h"
#include "Guard.h"


	HUD::HUD() {
	

	guardRep = 100;
	prisonerRep = 100;
}


	void HUD::drawMissions(sf::View &view, sf::RenderWindow &window) {
	


	MissionsBox.setSize(sf::Vector2f(250, 400));
	MissionsBox.setFillColor(sf::Color(242, 232, 171, HUDopacity));
	MissionsBox.setOutlineThickness(2);
	MissionsBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	MissionsBox.setPosition(view.getCenter().x - 125, view.getCenter().y - 130);

	sf::Text MissionsHeader;
	MissionsHeader.setFont(HUDFont);
	MissionsHeader.setFillColor(sf::Color(0, 0, 0, HUDopacity));
	MissionsHeader.setString("Missions");
	MissionsHeader.setCharacterSize(35);
	MissionsHeader.setPosition(MissionsBox.getPosition().x + 50, MissionsBox.getPosition().y + 20);
	
	window.draw(MissionsBox);
	window.draw(MissionsHeader);
	for (int i = 0; i < missions.size(); i++) {
		std::cout << "Mission Size: " << missions.size() << std::endl;
		missions[i].setCharacterSize(25);
		missions[i].setPosition(view.getCenter().x - 115, (view.getCenter().y - 70) + (i * 20));
		window.draw(missions[i]);
	}

}

	void HUD::drawSkills(sf::View &view, sf::RenderWindow &window) {
	SkillsBox.setSize(sf::Vector2f(250, 370));
	SkillsBox.setFillColor(sf::Color(100, 100, 100, HUDopacity));
	SkillsBox.setOutlineThickness(2);
	SkillsBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	SkillsBox.setPosition(view.getCenter().x - 390, view.getCenter().y - 130);


	std::string StrengthString = std::to_string(playerStrength); // converting the int to string, so player knows the stats
	std::string StaminaString = std::to_string(playerStamina);
	std::string ArmourString = std::to_string(playerArmour);
	std::string CharismaString = std::to_string(playerCharisma);
	std::string KnowledgeString = std::to_string(playerKnowledge);

	StrengthBar.setSize(sf::Vector2f(200, 20));
	StrengthBar.setFillColor(sf::Color(255, 0, 0, HUDopacity));
	StrengthBar.setOutlineThickness(2);
	StrengthBar.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	Strength.setSize(sf::Vector2f((playerStrength * 2), 20));
	Strength.setFillColor(sf::Color(237, 221, 80, HUDopacity));

	StaminaBar.setSize(sf::Vector2f(200, 20));
	StaminaBar.setFillColor(sf::Color(255, 0, 0, HUDopacity));
	StaminaBar.setOutlineThickness(2);
	StaminaBar.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	Stamina.setSize(sf::Vector2f((playerStamina * 2), 20));
	Stamina.setFillColor(sf::Color(32, 157, 234, HUDopacity));

	ArmourBar.setSize(sf::Vector2f(200, 20));
	ArmourBar.setFillColor(sf::Color(255, 0, 0, HUDopacity));
	ArmourBar.setOutlineThickness(2);
	ArmourBar.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	Armour.setSize(sf::Vector2f((playerArmour * 2), 20));
	Armour.setFillColor(sf::Color(175, 219, 206, HUDopacity));

	CharismaBar.setSize(sf::Vector2f(200, 20));
	CharismaBar.setFillColor(sf::Color(255, 0, 0, HUDopacity));
	CharismaBar.setOutlineThickness(2);
	CharismaBar.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	Charisma.setSize(sf::Vector2f((playerCharisma * 2), 20));
	Charisma.setFillColor(sf::Color(155, 71, 216, HUDopacity));

	KnowledgeBar.setSize(sf::Vector2f(200, 20));
	KnowledgeBar.setFillColor(sf::Color(255, 0, 0, HUDopacity));
	KnowledgeBar.setOutlineThickness(2);
	KnowledgeBar.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	Knowledge.setSize(sf::Vector2f((playerKnowledge * 2), 20));
	Knowledge.setFillColor(sf::Color(70, 234, 60, HUDopacity));

	sf::Text SkillsText, strengthText, staminaText, armourText, charismaText, knowledgeText;
	SkillsText.setFont(HUDFont);
	SkillsText.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	SkillsText.setString("Skills");
	SkillsText.setCharacterSize(30);

	strengthText.setFont(HUDFont2);
	strengthText.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	strengthText.setString("Strength: " + StrengthString);
	strengthText.setCharacterSize(35);

	staminaText.setFont(HUDFont2);
	staminaText.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	staminaText.setString("Stamina: " + StaminaString);
	staminaText.setCharacterSize(35);

	armourText.setFont(HUDFont2);
	armourText.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	armourText.setString("Endurance: " + ArmourString);
	armourText.setCharacterSize(35);

	charismaText.setFont(HUDFont2);
	charismaText.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	charismaText.setString("Charisma: " + CharismaString);
	charismaText.setCharacterSize(35);

	knowledgeText.setFont(HUDFont2);
	knowledgeText.setString("Knowledge: " + KnowledgeString);
	knowledgeText.setCharacterSize(35);



	SkillsText.setPosition(SkillsBox.getPosition().x + 75, SkillsBox.getPosition().y + 10);
	strengthText.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 40); // setting the position relative to the skillbox
	staminaText.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 100);
	armourText.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 160);
	charismaText.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 220);
	knowledgeText.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 280);

	StrengthBar.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 85); // these are the empty stat bars
	StaminaBar.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 145);
	ArmourBar.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 205);
	CharismaBar.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 265);
	KnowledgeBar.setPosition(SkillsBox.getPosition().x + 20, SkillsBox.getPosition().y + 325);

	Strength.setPosition(StrengthBar.getPosition().x, StrengthBar.getPosition().y); // setting the positions to the respective bars
	Stamina.setPosition(StaminaBar.getPosition().x, StaminaBar.getPosition().y);
	Armour.setPosition(ArmourBar.getPosition().x, ArmourBar.getPosition().y);
	Charisma.setPosition(CharismaBar.getPosition().x, CharismaBar.getPosition().y);
	Knowledge.setPosition(KnowledgeBar.getPosition().x, KnowledgeBar.getPosition().y);

	window.draw(SkillsBox);
	window.draw(SkillsText);
	window.draw(strengthText);
	window.draw(staminaText);
	window.draw(armourText);
	window.draw(charismaText);
	window.draw(knowledgeText);

	window.draw(StrengthBar);
	window.draw(StaminaBar);
	window.draw(ArmourBar);
	window.draw(CharismaBar);
	window.draw(KnowledgeBar);

	window.draw(Strength);
	window.draw(Stamina);
	window.draw(Armour);
	window.draw(Charisma);
	window.draw(Knowledge);

	
}

void HUD::MouseInput(sf::RenderWindow &window) {
	sf::Vector2i mousePos = ::sf::Mouse::getPosition(window); // getting the position of the mouse relative to the window
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // left mouse button
		if (mousePos.y >= box.getPosition().y && mousePos.y <= box.getPosition().y + box.getSize().y) { // if the y position is between the HUD button
			if (mousePos.x >= box.getPosition().x && mousePos.x <= box.getPosition().x + box.getSize().x) { // if the x position is on the first HUD button
			//Box 1
				std::cout << "Missions" << std::endl;
				missionsOpening();
			}

			if (mousePos.x >= box1.getPosition().x && mousePos.x <= box1.getPosition().x + box1.getSize().x) { // if the x position is on the first HUD button
				std::cout << "Skills" << std::endl;
				skillsOpening();
			}

			if (mousePos.x >= box2.getPosition().x && mousePos.x <= box2.getPosition().x + box2.getSize().x) { // if the x position is on the first HUD button
				//Box 3
				std::cout << "Inventory" << std::endl;
				inventoryOpening();
			}
		}
		//Crafting button
		if (mousePos.x >= CraftButton.getPosition().x && mousePos.x <= CraftButton.getPosition().x + CraftButton.getSize().x) {
			if (mousePos.y >= CraftButton.getPosition().y && mousePos.y <= CraftButton.getPosition().y + CraftButton.getSize().y) {
				craftingOpening();
			}
		}
		if (mousePos.x >= CraftBox.getPosition().x && mousePos.x <= CraftBox.getPosition().x + CraftBox.getSize().x) {
			if (mousePos.y >= CraftBox.getPosition().y && mousePos.y <= CraftBox.getPosition().y + CraftBox.getSize().y) {
				craftButtonClicked();
			}
		}
	}
}

void HUD::skillsOpening() {
	if (MisOpen == false && InvOpen == false) {
		SkilOpenCount++; // incrementing to know if the player has hit the key a second time	

		if ((SkilOpen = true) && SkilOpenCount >= 2) { // if the misOpenCount is 2, return the value back to 0, and turn the missions open screen to false, to stop drawing
			std::cout << "skills Closed" << std::endl;
			SkilOpenCount = 0;
			SkilOpen = false; // shutting the Missions screen down
		}
		else {
			std::cout << "skills Open" << std::endl;
			SkilOpen = true; // opening missions screen, drawing it to screen
		}
	}
}
void HUD::missionsOpening() {
	if (SkilOpen == false && InvOpen == false) {
		MisOpenCount++; // incrementing to know if the player has hit the key a second time	

		if ((MisOpen = true) && MisOpenCount >= 2) { // if the misOpenCount is 2, return the value back to 0, and turn the missions open screen to false, to stop drawing
			std::cout << "Missions Closed" << std::endl;
			MisOpenCount = 0;
			MisOpen = false; // shutting the Missions screen down
		}
		else {
			std::cout << "Missions Open" << std::endl;
			MisOpen = true; // opening missions screen, drawing it to screen
		}
	}
}
void HUD::inventoryOpening() {
	if (SkilOpen == false && MisOpen == false) {
		InvOpenCount++; // incrementing to know if the player has hit the key a second time	

		if ((InvOpen = true) && InvOpenCount >= 2) { // if the misOpenCount is 2, return the value back to 0, and turn the missions open screen to false, to stop drawing
			std::cout << "Inventory Closed" << std::endl;
			InvOpenCount = 0;
			InvOpen = false; // shutting the Missions screen down
		}
		else {
			std::cout << "Inventory Open" << std::endl;
			InvOpen = true; // opening missions screen, drawing it to screen

		}
	}
}
void HUD::reputationOpening() {
	RepOpenCount++; // incrementing to know if the player has hit the key a second time	

	if ((RepOpen = true) && RepOpenCount >= 2) { // if the repOpenCount is 2, return the value back to 0, and turn the reputation open screen to false, to stop drawing
		std::cout << "Reputation Closed" << std::endl;
		RepOpenCount = 0;
		RepOpen = false; // shutting the Missions screen down
	}
	else {
		std::cout << "Reputation Open" << std::endl;
		RepOpen = true; // opening missions screen, drawing it to screen
	}
}
void HUD::craftingOpening(){
	if (InvOpen == true) {
		craftOpenCount++;
		if ((craftOpen = true) && craftOpenCount >= 2) {
			craftOpenCount = 0;
			craftOpen = false;
		}
		else {
			craftOpen = true;
		}
	}
}
void HUD::craftButtonClicked() {
	std::cout << "Crafted Something" << std::endl;
	craftOpen = false;
	InvOpen = false;
}


	void HUD::HUDUserInput(sf::View &view, sf::RenderWindow &window) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { //skills
				skillsOpening();
				std::cout << "S pressed" << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) { //missions
				missionsOpening();
				std::cout << "M pressed" << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { //reputation
				reputationOpening();
				std::cout << "R pressed" << std::endl;


			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) { // inventory
				inventoryOpening();
				std::cout << "I pressed" << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				craftingOpening();
				std::cout << "C pressed" << std::endl;
			}
		}
	
	}

	void HUD::drawInventory(sf::View &view, sf::RenderWindow &window) {
		if (!characterTexture.loadFromFile("../assets/image_assets/sprite_image.png")) {
			std::cout << "Load fail Error on playerFaceTexture" << std::endl;
			system("pause");

		}
		InvSlot.resize(8);

		InventoryBox.setSize(sf::Vector2f(250, 420));
		InventoryBox.setFillColor(sf::Color(55, 55, 55, HUDopacity));
		InventoryBox.setOutlineThickness(2);
		InventoryBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
		InventoryBox.setPosition(view.getCenter().x + 140, view.getCenter().y - 150);

		characterBox.setSize(sf::Vector2f(150, 195));
		//characterBox.setFillColor(sf::Color(15, 15, 15, HUDopacity));
		characterBox.setTexture(&characterTexture);
		characterBox.setOutlineThickness(1);
		characterBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
		characterBox.setPosition(InventoryBox.getPosition().x + 5, InventoryBox.getPosition().y + 70);


		sf::Text InventoryText;
		InventoryText.setFont(HUDFont);
		InventoryText.setFillColor(sf::Color(255, 255, 255, HUDopacity));
		InventoryText.setString("Inventory");
		InventoryText.setCharacterSize(30);
		InventoryText.setPosition(InventoryBox.getPosition().x + 50, InventoryBox.getPosition().y + 10);
		
		
		for (int i = 0; i < InvSlot.size(); i++) {
			InvSlot[i].setSize(sf::Vector2f(40, 45));
			InvSlot[i].setOutlineThickness(1);
			InvSlot[i].setFillColor(sf::Color(15, 15, 15, HUDopacity));
			InvSlot[i].setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
			
			
		}
		InvSlot[0].setPosition(InventoryBox.getPosition().x + 160, InventoryBox.getPosition().y + 70);
		InvSlot[1].setPosition(InvSlot[0].getPosition().x, InvSlot[0].getPosition().y + 50);
		InvSlot[2].setPosition(InvSlot[1].getPosition().x, InvSlot[1].getPosition().y + 50);
		InvSlot[3].setPosition(InvSlot[2].getPosition().x, InvSlot[2].getPosition().y + 50);
		InvSlot[4].setPosition(InventoryBox.getPosition().x + 205, InventoryBox.getPosition().y + 70);
		InvSlot[5].setPosition(InvSlot[4].getPosition().x, InvSlot[4].getPosition().y + 50);
		InvSlot[6].setPosition(InvSlot[5].getPosition().x, InvSlot[5].getPosition().y + 50);
		InvSlot[7].setPosition(InvSlot[6].getPosition().x, InvSlot[6].getPosition().y + 50);

		

		CraftButton.setSize(sf::Vector2f(210, 100));
		CraftButton.setOutlineThickness(1);
		CraftButton.setFillColor(sf::Color(15, 15, 15, HUDopacity));
		CraftButton.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
		CraftButton.setPosition(InventoryBox.getPosition().x + 20, InventoryBox.getPosition().y + 280);

		sf::Text CraftText;
		CraftText.setFont(HUDFont);
		CraftText.setFillColor(sf::Color(255, 255, 255, HUDopacity));
		CraftText.setString("Crafting");
		CraftText.setCharacterSize(30);
		CraftText.setPosition(CraftButton.getPosition().x + 50, CraftButton.getPosition().y + 30);


		for (int i = 0; i < InvSlot.size(); i++) {
			window.draw(InvSlot[i]);
		}
		for (int i = 0; i < EmptySlot.size(); i++) {
			EmptySlot[i].setPosition(InvSlot[i].getPosition().x, InvSlot[i].getPosition().y);
			window.draw(EmptySlot[i]);
		}

		window.draw(InventoryBox);
		window.draw(InventoryText);
		window.draw(characterBox);
		window.draw(CraftButton);
		window.draw(CraftText);

	}


void HUD::drawReputation(sf::View &view, sf::RenderWindow &window) {
	emptyGRep.setSize(sf::Vector2f(200, 20));
	emptyGRep.setFillColor(sf::Color(0, 0, 255, HUDopacity));
	emptyGRep.setOutlineThickness(2);
	emptyGRep.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	GRep.setSize(sf::Vector2f(guardRep, 20));
	GRep.setFillColor(sf::Color(0, 128, 255, HUDopacity));

	emptyPRep.setSize(sf::Vector2f(200, 20));
	emptyPRep.setFillColor(sf::Color(255, 0, 0, HUDopacity));
	emptyPRep.setOutlineThickness(2);
	emptyPRep.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	PRep.setSize(sf::Vector2f(prisonerRep, 20));
	PRep.setFillColor(sf::Color(255, 51, 51, HUDopacity));
	
	emptyGRep.setPosition(view.getCenter().x - 70, view.getCenter().y - 200);
	GRep.setPosition(view.getCenter().x - 70, view.getCenter().y - 200);

	emptyPRep.setPosition(view.getCenter().x - 70, view.getCenter().y - 170);
	PRep.setPosition(view.getCenter().x - 70, view.getCenter().y - 170);

	if (prisonerRep <= 0) {
		prisonerRep = 0;
	}
	if (prisonerRep >= 200) {
		prisonerRep = 200;
	}

	if (guardRep <= 0) {
		guardRep = 0;
	}
	if (guardRep >= 200) {
		guardRep = 200;
	}

	window.draw(emptyGRep);
	window.draw(GRep);
	window.draw(emptyPRep);
	window.draw(PRep);
}


void HUD::drawHUD(sf::View &view, sf::RenderWindow &window) {
	if (XPcount >= maxXP) {
		XPcount = 0;
		playerLevel++; // incrementing the player level if the XP count is more than the max required XP
		healthBar += 20; // increasing the health of the player slightly, unless they have full health
		std::cout << playerLevel << std::endl;
	}

	if (healthBar >= 210) { // if the health is more than the maximum, keep it at the max HP(cant go over max HP)
		healthBar = 210;
	}
	if (playerLevel >= 100) {
		playerLevel = 100; //the maximum level is 100
	}
	if (!RoutineFont.loadFromFile("../assets/text_assets/FontFile.ttf")) {
		std::cout << "Load fail Error on HUDFont" << std::endl;
		system("pause");
	}
	if (!playerTexture.loadFromFile("../assets/image_assets/sprite_image.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");

	}
	if (!Skills.loadFromFile("../assets/image_assets/Skills.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");

	}
	if (!Inventory.loadFromFile("../assets/image_assets/Inventory.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");

	}
	if (!Missions.loadFromFile("../assets/image_assets/Missions.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");

	}
	if (!halfHealthPlayer.loadFromFile("../assets/image_assets/halfHealth_sprite_image.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");

	}
	if (!lowHealthPlayer.loadFromFile("../assets/image_assets/lowHealth_sprite_image.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");

	}
	if (!HUDFont.loadFromFile("../assets/text_assets/CagedPrisoner.ttf")) {
		std::cout << "Load fail Error on HUDFont" << std::endl;
		system("pause");
	}
	if (!HUDFont2.loadFromFile("../assets/text_assets/FontFile.ttf")) {
		std::cout << "Load fail Error on HUDFont" << std::endl;
		system("pause");
	}

	if (!poundTexture.loadFromFile("../assets/image_assets/PrisonPound.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");

	}

	//Routine routine;

	prisonPound.setSize(sf::Vector2f(50, 50));
	prisonPound.setTexture(&poundTexture);
	prisonPound.setPosition(view.getCenter().x - 25, view.getCenter().y - 280);
	
	std::string moneyString = std::to_string(prisonMoney);
	sf::Text moneyText;
	moneyText.setFont(HUDFont2);
	moneyText.setString(moneyString);
	moneyText.setFillColor(sf::Color(0, 0, 0));
	moneyText.setPosition(view.getCenter().x + 25, view.getCenter().y - 275);

	CashBox.setSize(sf::Vector2f(150, 70));
	CashBox.setFillColor(sf::Color(50, 50, 50, HUDopacity));
	CashBox.setOutlineThickness(2);
	CashBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	CashBox.setPosition(view.getCenter().x - 35, view.getCenter().y - 290);

	sf::Text HealthText, LevelText, LevelString, XPText, TimerText, dayText, dateText;
	HealthText.setFont(HUDFont);
	HealthText.setString("Health");
	HealthText.setCharacterSize(20);
	HealthText.setPosition(view.getCenter().x - 250, view.getCenter().y - 282);



	XPText.setFont(HUDFont);
	XPText.setString("XP");
	XPText.setCharacterSize(20);
	XPText.setPosition(view.getCenter().x - 220, view.getCenter().y - 252);

	//std::cout << TimeElapsed.asSeconds() << std::endl; 


	std::string MinutesString = std::to_string(HUDTimeMinute);
	std::string SecondsString = std::to_string(HUDTime);
	std::string dayString = std::to_string(day);

	dayText.setFont(HUDFont2);
	dayText.setString("Day : " + dayString);
	dayText.setFillColor(sf::Color(0, 0, 0));
	dayText.setPosition(view.getCenter().x + 235, view.getCenter().y - 285);



	TimerText.setFont(HUDFont2);
	if (HUDTimeMinute <= 9 && HUDTime <= 9) { // if both HUDTime and HUDTimeMinute is less than 9, put a 0 before both 
		TimerText.setString("0" + MinutesString + " : 0" + SecondsString);
	}
	else if (HUDTime <= 9) { // if the HUDTime seconds is less than 9, have a 0 before the number, so it's digital time
		TimerText.setString(MinutesString + " : 0" + SecondsString);
	}
	else if (HUDTimeMinute <= 9) { // ig HUDTimeMinute is less than 9, but a 0 before the minutes
		TimerText.setString("0" + MinutesString + " : " + SecondsString);
	}
	else {
		TimerText.setString(MinutesString + " : " + SecondsString);

	}

	TimerText.setFillColor(sf::Color(0, 0, 0));
	TimerText.setPosition(view.getCenter().x + 235, view.getCenter().y - 245);

	PlayerIcon.setRadius(35);
	if (healthBar >= 110) {
		PlayerIcon.setTexture(&playerTexture);
	}
	else if (healthBar >= 40 && healthBar <= 110) {
		PlayerIcon.setTexture(&halfHealthPlayer);
	}
	else {
		PlayerIcon.setTexture(&lowHealthPlayer);
	}
	PlayerIcon.setTextureRect(sf::IntRect(0, 0, 50, 100));
	PlayerIcon.setOutlineThickness(1);
	PlayerIcon.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	PlayerBox.setSize(sf::Vector2f(310, 150));
	PlayerBox.setFillColor(sf::Color(50, 50, 50, HUDopacity));
	PlayerBox.setOutlineThickness(2);
	PlayerBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	LevelText.setFont(HUDFont2); // level text under the character icon
	LevelText.setString("Level:");
	LevelText.setCharacterSize(35);
	LevelText.setPosition(view.getCenter().x - 370, view.getCenter().y - 220);


	std::string lvlString = std::to_string(playerLevel);
	LevelString.setFont(HUDFont2);
	LevelString.setString(lvlString);
	LevelString.setCharacterSize(35);
	LevelString.setPosition(view.getCenter().x - 370, view.getCenter().y - 190);

	noHealth.setSize(sf::Vector2f(210, 20));
	noHealth.setFillColor(sf::Color(255, 0, 0, HUDopacity));
	noHealth.setOutlineThickness(2);
	noHealth.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	health.setSize(sf::Vector2f(healthBar, 20));
	health.setFillColor(sf::Color(0, 255, 0, HUDopacity));

	noXP.setSize(sf::Vector2f(210, 20));
	noXP.setFillColor(sf::Color(100, 100, 100, HUDopacity));
	noXP.setOutlineThickness(2);
	noXP.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));

	XP.setSize(sf::Vector2f(XPcount, 20));
	XP.setFillColor(sf::Color(234, 149, 37, HUDopacity));

	PlayerIcon.setPosition(view.getCenter().x - 380, view.getCenter().y - 280);
	PlayerBox.setPosition(view.getCenter().x - 390, view.getCenter().y - 290);
	noHealth.setPosition(view.getCenter().x - 300, view.getCenter().y - 280);
	health.setPosition(view.getCenter().x - 300, view.getCenter().y - 280);

	noXP.setPosition(view.getCenter().x - 300, view.getCenter().y - 250);
	XP.setPosition(view.getCenter().x - 300, view.getCenter().y - 250);


	box.setSize(sf::Vector2f(50, 50));
	box.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	box.setTexture(&Missions);
	box.setOutlineThickness(1);
	box.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	box.setPosition(view.getCenter().x - 160, view.getCenter().y - 220);

	box1.setSize(sf::Vector2f(50, 50));
	box1.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	box1.setTexture(&Skills);
	box1.setOutlineThickness(1);
	box1.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	box1.setPosition(view.getCenter().x - 220, view.getCenter().y - 220);

	box2.setSize(sf::Vector2f(50, 50));
	box2.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	box2.setTexture(&Inventory);
	box2.setOutlineThickness(1);
	box2.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	box2.setPosition(view.getCenter().x - 280, view.getCenter().y - 220);


	clockOuterBox.setSize(sf::Vector2f(170, 130));
	clockOuterBox.setOutlineThickness(2);
	clockOuterBox.setFillColor(sf::Color(155, 155, 155, HUDopacity));
	clockOuterBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	clockOuterBox.setPosition(view.getCenter().x + 220, view.getCenter().y - 290);

	date.setSize(sf::Vector2f(150, 30));
	date.setOutlineThickness(2);
	date.setFillColor(sf::Color(50, 50, 50, HUDopacity));
	date.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	date.setPosition(view.getCenter().x + 230, view.getCenter().y - 280);

	clockDigital.setSize(sf::Vector2f(150, 30));
	clockDigital.setOutlineThickness(2);
	clockDigital.setFillColor(sf::Color(50, 50, 50, HUDopacity));
	clockDigital.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	clockDigital.setPosition(view.getCenter().x + 230, view.getCenter().y - 240);

	routineBox.setSize(sf::Vector2f(150, 30));
	routineBox.setOutlineThickness(2);
	routineBox.setFillColor(sf::Color(50, 50, 50, HUDopacity));
	routineBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	routineBox.setPosition(view.getCenter().x + 230, view.getCenter().y - 200);

	

	sf::Time TimeElapsed = HUDClock.getElapsedTime(); // setting the time to the hud clock, so it can count seconds
	sf::Time seconds = sf::seconds(1); // this is to compare to the time elapsed to get 1 second
	int Minute = 60;



	if (TimeElapsed >= seconds) { // if the time elapsed is a second, increment the HUDTime and restart the HUDClock 
		HUDTime++;
		HUDClock.restart();
		//std::cout << "Minutes: " << HUDTimeMinute << ", Seconds: " << HUDTime << std::endl;

		if (HUDTimeMinute >= 20 && HUDTimeMinute <= 22) { //between the 20th and 22nd minute, increase the nighttime
			if (night < 100) {
				night++;
			}
		}

		if (HUDTimeMinute >= 5 && HUDTimeMinute <= 7) {
			if (night > 0) {
				night--;
			}
		}
	}

	if (HUDTime >= Minute) { // if the HUDTime is more or equal to 60, do this
		HUDTimeMinute++; // increment the hud time minute
		HUDTime = 0; // change the hud time back to 0
		if (HUDTimeMinute >= 24) {// if the hudtime minute is more than 24(like a 24 hour clock)
			day++;
			HUDTimeMinute = 0; // set hudtime back to 0
		}
	
		
	}

	sf::RectangleShape daynight(sf::Vector2f(800, 600));
	daynight.setFillColor(sf::Color(0, 0, 255, night));
	daynight.setOrigin(400, 300);

	daynight.setPosition(view.getCenter()); //setting the day night to the view


	window.draw(daynight);

	window.draw(PlayerBox);
	window.draw(box);
	window.draw(box1);
	window.draw(box2);
	window.draw(PlayerIcon);
	window.draw(noHealth);
	window.draw(health);
	window.draw(noXP);
	window.draw(XP);

	window.draw(clockOuterBox);
	window.draw(CashBox);
	window.draw(date);
	window.draw(clockDigital);
	window.draw(routineBox);

	window.draw(HealthText);
	window.draw(XPText);
	window.draw(TimerText);
	window.draw(dayText);
	window.draw(LevelText);
	window.draw(LevelString);
	window.draw(prisonPound);
	window.draw(moneyText);	  

	Times(view, window);
}


std::string prisonerFile("../assets/text_assets/prisoners.txt");
void HUD::Times(sf::View &view, sf::RenderWindow &window) {
	sf::Text RoutineDialogue;
	std::vector<sf::Text>  routine(6, sf::Text(RoutineDialogue)); // an array of 5 cell doorsa

	routine[0].setString("Chow Time");
	routine[1].setString("Work Time");
	routine[2].setString("Shower Time");
	routine[3].setString("Yard Time");
	routine[4].setString("Bed Time");
	routine[5].setString("Free Time");
	


	for (int i = 0; i < routine.size(); i++) {
		routine[i].setFont(RoutineFont);
		routine[i].setCharacterSize(40);
		routine[i].setFillColor(sf::Color(255, 255, 255));
		routine[i].setPosition(view.getCenter().x + 260, view.getCenter().y - 210);
	}

	if (HUDTimeMinute >= 0 && HUDTimeMinute <= 6) { // if between 0 - 7
		window.draw(routine[4]); // bed time
		bedTime = true;
	
	}
	else if (HUDTimeMinute >= 7 && HUDTimeMinute <= 7) { // if 8
		window.draw(routine[0]); // chow time
		bedTime = false;
		chowTime = true;
	}
	else if (HUDTimeMinute >= 8 && HUDTimeMinute <= 8) { // if 8
		window.draw(routine[3]); // yard time
		chowTime = false;
		yardTime = true;
	}
	else if (HUDTimeMinute >= 9 && HUDTimeMinute <= 12) { // if 9-12
		window.draw(routine[1]); // work
		yardTime = false;
		workTime = true;

	}
	else if (HUDTimeMinute >= 13 && HUDTimeMinute <= 13) { // if 13
		window.draw(routine[0]); // chow time
		workTime = false;
		chowTime = true;
		
	}
	else if (HUDTimeMinute >= 14 && HUDTimeMinute <= 17) { // if 14-17
		window.draw(routine[1]); // work time
		chowTime = false;
		workTime = true;
	}
	else if (HUDTimeMinute >= 18 && HUDTimeMinute <= 18) { // if 18
		window.draw(routine[0]); // chow time
		workTime = false;
		chowTime = true;
		
	}
	else if (HUDTimeMinute >= 19 && HUDTimeMinute <= 19) { // if 19
		window.draw(routine[2]); // shower time
		chowTime = false;
		showerTime = true;
	
	}
	else if (HUDTimeMinute > 19 && HUDTimeMinute <= 22) { // if 20-22
		window.draw(routine[5]);// free time
		showerTime = false;
		freeTime = true;
		
	} else if (HUDTimeMinute >= 23 && HUDTimeMinute <= 23) { // if 23
		window.draw(routine[4]);//bedtime
		freeTime = false;
		bedTime = true;
	}
	
}

void HUD::drawCraft(sf::View &view, sf::RenderWindow &window) {
	CraftBox.setSize(sf::Vector2f(250, 250));
	CraftBox.setOutlineThickness(1);
	CraftBox.setFillColor(sf::Color(15, 15, 15, HUDopacity));
	CraftBox.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	CraftBox.setPosition(view.getCenter().x - 150, view.getCenter().y - 120);
	
	submitCraft.setSize(sf::Vector2f(210, 75));
	submitCraft.setOutlineThickness(1);
	submitCraft.setFillColor(sf::Color(15, 15, 15, HUDopacity));
	submitCraft.setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
	submitCraft.setPosition(CraftBox.getPosition().x + 20, CraftBox.getPosition().y + 150);


	sf::Text submitText;
	submitText.setFont(HUDFont);
	submitText.setFillColor(sf::Color(255, 255, 255, HUDopacity));
	submitText.setString("Craft Item");
	submitText.setCharacterSize(30);
	submitText.setPosition(submitCraft.getPosition().x + 40, submitCraft.getPosition().y + 20);

	
	std::vector<sf::RectangleShape>  inputBox(4, sf::RectangleShape(craftInputBox)); // an array of 5 cell doorsa

	for (int i = 0; i < inputBox.size(); i++) {

		inputBox[i].setSize(sf::Vector2f(50, 50));
		inputBox[i].setOutlineThickness(1);
		inputBox[i].setFillColor(sf::Color(15, 15, 15, HUDopacity));
		inputBox[i].setOutlineColor(sf::Color(0, 0, 0, HUDopacity));
		//inputBox[i].setTexture(&cellTexture);

	}



	inputBox[0].setPosition(CraftBox.getPosition().x + 80, CraftBox.getPosition().y + 20);
	inputBox[1].setPosition(CraftBox.getPosition().x + 130, CraftBox.getPosition().y + 20);
	inputBox[2].setPosition(CraftBox.getPosition().x + 80, CraftBox.getPosition().y + 70);
	inputBox[3].setPosition(CraftBox.getPosition().x + 130, CraftBox.getPosition().y + 70);



	if (craftOpen = true) {
		window.draw(CraftBox);
		window.draw(submitCraft);
		window.draw(submitText);
		for (int i = 0; i < inputBox.size(); i++) {
			window.draw(inputBox[i]);
		}
	}

}