#include "prisonerDialogue.h"


prisonerDialogue::prisonerDialogue()
{
	prisonerDState = prisonerDialogueMenu; // setting the state for the dialogue
	
	//hud.guardRep; // these are the 2 ints were going to be incrementing and decremening and using for the missions and trading
	//hud.prisonerRep;
	if (!font.loadFromFile("../assets/text_assets/FontFile.ttf"))
	{
		// error...
		//	std::cout << "Error loading file" << std::endl;
		system("pause");
	}
	PM.resize(7);
	PM[0] = "I need a distraction";
	PM[1] = "Go Get me a weapon";
	PM[2] = "I need some food";
	PM[3] = "Find me some wood";
	PM[4] = "I need a guard uniform";
	PM[5] = "I want the warden to pay";
	PM[6] = "Go beat up a SWAT member";

	PrisonerText[0].setFont(font);
	PrisonerText[0].setCharacterSize(50);
	PrisonerText[0].setFillColor(sf::Color::Blue);
	PrisonerText[0].setString("Talk");
	

	PrisonerText[1].setFont(font);
	PrisonerText[1].setCharacterSize(50);
	PrisonerText[1].setFillColor(sf::Color::Black);
	PrisonerText[1].setString("Trade");
	
	PrisonerText[2].setFont(font);
	PrisonerText[2].setCharacterSize(50);
	PrisonerText[2].setFillColor(sf::Color::Black);
	PrisonerText[2].setString("Mission");


	prisonItemIndex = 0;

	

}

prisonerDialogue::~prisonerDialogue()
{
}

void prisonerDialogue::drawDialogueBox(sf::View &view, sf::RenderWindow &window) {
	DialogueBox.setSize(sf::Vector2f(400, 200));
	DialogueBox.setFillColor(sf::Color(239, 239, 167));
	DialogueBox.setOutlineThickness(2);
	DialogueBox.setOutlineColor(sf::Color(0, 0, 0, 255));
	DialogueBox.setPosition(view.getCenter().x - 200, view.getCenter().y + 80);

	window.draw(DialogueBox);
	
	
}

void prisonerDialogue::draw(sf::View &view, sf::RenderWindow &window) {

	std::vector<sf::RectangleShape>  BoxSegment(3, sf::RectangleShape(segBox)); // an array of 5 cell doors

	for (int i = 0; i < BoxSegment.size(); i++) {

		BoxSegment[i].setSize(sf::Vector2f(DialogueBox.getSize().x - 40, 50));
		BoxSegment[i].setFillColor(sf::Color(255, 0, 0));
		BoxSegment[i].setOutlineThickness(1);
		BoxSegment[i].setOutlineColor(sf::Color(0, 0, 0, 255));
	}
	int offset = 12;

	BoxSegment[0].setPosition(DialogueBox.getPosition().x + 20, DialogueBox.getPosition().y + offset);
	BoxSegment[1].setPosition(DialogueBox.getPosition().x + 20, BoxSegment[0].getPosition().y + offset + 50);
	BoxSegment[2].setPosition(DialogueBox.getPosition().x + 20, BoxSegment[1].getPosition().y + offset + 50);

	

	for (int i = 0; i < BoxSegment.size(); i++) {
		window.draw(BoxSegment[i]);
	}
	PrisonerText[0].setPosition(view.getCenter().x, view.getCenter().y + 80); // center item for width, have the amount of string items + 1, so that they're equally spaced out
	PrisonerText[1].setPosition(view.getCenter().x, view.getCenter().y + 140); // center item for width, have the amount of string items + 1, so that they're equally spaced out
	PrisonerText[2].setPosition(view.getCenter().x, view.getCenter().y + 200); // center item for width, have the amount of string items + 1, so that they're equally spaced out


	for (int i = 0; i < prisoner_item_Number; i++) {
		window.draw(PrisonerText[i]);
	}

}

void prisonerDialogue::Up() {
	if (prisonItemIndex - 1 >= 0) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		PrisonerText[prisonItemIndex].setFillColor(sf::Color::Black); //set the blue color to white
		prisonItemIndex--; //decrememnt the index
		PrisonerText[prisonItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}

void prisonerDialogue::Down() {
	if (prisonItemIndex + 1 < prisoner_item_Number) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		PrisonerText[prisonItemIndex].setFillColor(sf::Color::Black); //set the blue color to white
		prisonItemIndex++; // increment the index
		PrisonerText[prisonItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}

void prisonerDialogue::Talk(sf::View &view, sf::RenderWindow &window) {
	if (!cancelTexture.loadFromFile("../assets/image_assets/cancelButton.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");
	}

	cancelButton.setSize(sf::Vector2f(25, 25));
	cancelButton.setTexture(&cancelTexture);
	cancelButton.setPosition(view.getCenter().x + 155, view.getCenter().y + 240);


	std::vector<sf::Text>  talking(7, sf::Text(TalkDialogue)); // an array of 5 cell doorsa

	talking[0].setString("Don't drop the soap in the shower");
	talking[1].setString("There's going to be a breakout one of these days");
	talking[2].setString("The chow here is inedible");
	talking[3].setString("Man, I can't wait for visitation");
	talking[4].setString("I used to be a baller in the free world");
	talking[5].setString("Did I ever tell you I was a drug lord");
	talking[6].setString("I've killed like 5 guys with my bare hands");

	for (int i = 0; i < talking.size(); i++) {
		talking[i].setFont(font);
		talking[i].setCharacterSize(40);
		talking[i].setFillColor(sf::Color(0, 0, 0));
		talking[i].setPosition(view.getCenter().x - 170, view.getCenter().y + 90);
	}

	if (talkInt == 0) { window.draw(talking[0]); }
	else if (talkInt == 1) { window.draw(talking[1]); }
	else if (talkInt == 2) { window.draw(talking[2]); }
	else if (talkInt == 3) { window.draw(talking[3]); }
	else if (talkInt == 4) { window.draw(talking[4]); }
	else if (talkInt == 5) { window.draw(talking[5]); }
	else if (talkInt == 6) { window.draw(talking[6]); }
	window.draw(cancelButton);
}

void prisonerDialogue::Trade(sf::View &view, sf::RenderWindow &window) {
	if (!tradeTexture.loadFromFile("../assets/image_assets/TradeSymbol.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");
	}
	if (!tradeButtonTexture.loadFromFile("../assets/image_assets/TradeButton.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");
	}


	std::vector<sf::RectangleShape>  Boxes(4, sf::RectangleShape(tradeBox)); // an array of 5 cell doorsa
	for (int i = 0; i < Boxes.size(); i++) {
		Boxes[i].setSize(sf::Vector2f(50, 50));
		Boxes[i].setFillColor(sf::Color(155, 155, 155));
		Boxes[i].setOutlineThickness(2);
		Boxes[i].setOutlineColor(sf::Color(0, 0, 0));
	}

	Boxes[0].setPosition(view.getCenter().x - 160, view.getCenter().y + 120);
	Boxes[1].setPosition(view.getCenter().x - 160, view.getCenter().y + 170);
	Boxes[2].setPosition(view.getCenter().x + 110, view.getCenter().y + 120);
	Boxes[3].setPosition(view.getCenter().x + 110, view.getCenter().y + 170);

	tradeSymbol.setSize(sf::Vector2f(200, 100));
	tradeSymbol.setTexture(&tradeTexture);
	tradeSymbol.setPosition(view.getCenter().x - 100, view.getCenter().y + 120);

	
	tradeButton.setSize(sf::Vector2f(150, 50));
	tradeButton.setTexture(&tradeButtonTexture);
	tradeButton.setOutlineThickness(2);
	tradeButton.setOutlineColor(sf::Color(0, 0, 0));
	tradeButton.setPosition(view.getCenter().x - 75, view.getCenter().y + 225);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		std::cout << "Trade Made" << std::endl; // use this for trade functionality later
		prisonerDState = prisonerDialogueMenu;
		dialogueCheck = false;
	}

	for (int i = 0; i < Boxes.size(); i++) {
		window.draw(Boxes[i]);
	}
	window.draw(tradeSymbol);
	window.draw(tradeButton);

}

void prisonerDialogue::Mission(sf::View &view, sf::RenderWindow &window, HUD &hud) {

	if (!acceptTexture.loadFromFile("../assets/image_assets/acceptButton.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");
	}
	if (!declineTexture.loadFromFile("../assets/image_assets/declineButton.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");
	}
	declineButton.setSize(sf::Vector2f(150, 50));
	declineButton.setTexture(&declineTexture);
	declineButton.setOutlineThickness(2);
	declineButton.setOutlineColor(sf::Color(0, 0, 0));
	declineButton.setPosition(view.getCenter().x + 25, view.getCenter().y + 225);

	acceptButton.setSize(sf::Vector2f(150, 50));
	acceptButton.setTexture(&acceptTexture);
	acceptButton.setOutlineThickness(2);
	acceptButton.setOutlineColor(sf::Color(0, 0, 0));
	acceptButton.setPosition(view.getCenter().x - 175, view.getCenter().y + 225);

	
	missions.resize(7);
	missions[0].setString(PM[0]);
	missions[1].setString(PM[1]);
	missions[2].setString(PM[2]);
	missions[3].setString(PM[3]);
	missions[4].setString(PM[4]);
	missions[5].setString(PM[5]);
	missions[6].setString(PM[6]);

	for (int i = 0; i < missions.size(); i++) {
		missions[i].setFont(font);
		missions[i].setCharacterSize(40);
		missions[i].setFillColor(sf::Color(0, 0, 0));
		missions[i].setPosition(view.getCenter().x - 170, view.getCenter().y + 90);
	}
	

	
	acceptedMission.resize(missions.size(), false); // setting the size to the missions size and setting them to false
	if (missionsInt == 0) { window.draw(missions[0]); 	}
	else if (missionsInt == 1) { window.draw(missions[1]); 	}	
	else if (missionsInt == 2) { window.draw(missions[2]);	}
	else if (missionsInt == 3) { window.draw(missions[3]); 	}
	else if (missionsInt == 4) { window.draw(missions[4]); 	}
	else if (missionsInt == 5) { window.draw(missions[5]); 	}
	else if (missionsInt == 6) { window.draw(missions[6]); 	}


		
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		std::cout << "Mission Accepted:" << missionsInt << std::endl; // use this for trade functionality later, give positive rep to player for accepting
		prisonerDState = prisonerDialogueMenu;
		hud.missions.push_back(missions[missionsInt]);
		std::cout << "Mission Accepted: " << missionsInt << std::endl;
		dialogueCheck = false;
	}



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		std::cout << "Mission Declined" << std::endl; // use this for trade functionality later,give negative rep to player for declining
		prisonerDState = prisonerDialogueMenu;
		dialogueCheck = false;
	}

	window.draw(acceptButton);
	window.draw(declineButton);
}



void prisonerDialogue::dialogueHandler(sf::View &view, sf::RenderWindow &window, HUD &hud) {

	
	if (prisonerDState == prisonerDialogueMenu) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			Up();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			Down();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			switch (GetPressedItem()) {
			case 0: std::cout << "Talk" << std::endl;
					hud.prisonerRep += 2;
					prisonerDState = prisonerTalk; // setting the state to prisoner talk
					talkInt = rand() % 7;
				std::cout << "prisonRep: " << hud.prisonerRep << std::endl;
				break;
			case 1: std::cout << "Trade" << std::endl;
				if (hud.prisonerRep > 30) {
					hud.guardRep -= 2;
					hud.prisonerRep += 5;
				prisonerDState = prisonerTrade;// setting the state to prisoner trade
				}
				else {
					std::cout << "You need at least 20 prisoner rep to do this" << std::endl;
				}
				break;
			case 2: std::cout << "Missions" << std::endl;
				if (hud.prisonerRep > 60) {
					hud.prisonerRep += 7;
					hud.guardRep -= 5;
					prisonerDState = prisonerMissions;// setting the state to prisoner missions
					missionsInt = rand() % 7;
				}
				else {
					std::cout << "You need at least 40 prisoner rep to do this" << std::endl;
				}
				break;

			}
		}
	}

	if (prisonerDState == prisonerDialogueMenu) {
		drawDialogueBox(view, window);
		draw(view, window);
		std::cout << "prison dialogue menu drawn" << std::endl;

	}
	//PRISONER_______________________________________________
	if (prisonerDState == prisonerTalk) {
		drawDialogueBox(view, window);
	
		Talk(view, window);
		guardD.prisonInfo = 1;

	}
	if (prisonerDState == prisonerTrade) {
		drawDialogueBox(view, window);
		Trade(view, window);

	}
	if (prisonerDState == prisonerMissions) {
		drawDialogueBox(view, window);
		Mission(view, window, hud);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		prisonerDState = prisonerDialogueMenu;
		dialogueCheck = false;
	}
}