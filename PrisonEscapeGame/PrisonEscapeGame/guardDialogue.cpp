#include "guardDialogue.h"


guardDialogue::guardDialogue()
{
	guardDState = guardDialogueMenu; // setting the state for the dialogue
	if (!font.loadFromFile("../assets/text_assets/FontFile.ttf"))
	{
		// error...
		//	std::cout << "Error loading file" << std::endl;
		system("pause");
	}
	GuardText[0].setFont(font);
	GuardText[0].setCharacterSize(50);
	GuardText[0].setFillColor(sf::Color::Blue);
	GuardText[0].setString("Talk");


	GM1 = "I need you to help break up a fight";
	GM2 = "I need you to retrieve a guard uniform";
	GM3 = "Find me hidden weapons";
	GM4 = "Go find me some scrap metal";
	GM5 = "Snitch on 5 prisoners";
	GM6 = "Find some information for me";
	GM7 = "Go find me a cookie";

	GuardText[1].setFont(font);
	GuardText[1].setCharacterSize(50);
	GuardText[1].setFillColor(sf::Color::Black);
	GuardText[1].setString("Snitch");

	GuardText[2].setFont(font);
	GuardText[2].setCharacterSize(50);
	GuardText[2].setFillColor(sf::Color::Black);
	GuardText[2].setString("Mission");



	guardItemIndex = 0;
}


guardDialogue::~guardDialogue()
{
}
void guardDialogue::drawDialogueBox(sf::View &view, sf::RenderWindow &window) {
	DialogueBox.setSize(sf::Vector2f(400, 200));
	DialogueBox.setFillColor(sf::Color(239, 239, 167));
	DialogueBox.setOutlineThickness(2);
	DialogueBox.setOutlineColor(sf::Color(0, 0, 0, 255));
	DialogueBox.setPosition(view.getCenter().x - 200, view.getCenter().y + 80);

	

	window.draw(DialogueBox);

	
}

void guardDialogue::draw(sf::View &view, sf::RenderWindow &window) {
	std::vector<sf::RectangleShape>  BoxSegment(3, sf::RectangleShape(segBox)); // an array of 5 cell doors

	for (int i = 0; i < BoxSegment.size(); i++) {

		BoxSegment[i].setSize(sf::Vector2f(DialogueBox.getSize().x - 40, 50));
		BoxSegment[i].setFillColor(sf::Color(0, 213, 255));
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
	GuardText[0].setPosition(view.getCenter().x, view.getCenter().y + 80); // center item for width, have the amount of string items + 1, so that they're equally spaced out
	GuardText[1].setPosition(view.getCenter().x, view.getCenter().y + 140); // center item for width, have the amount of string items + 1, so that they're equally spaced out
	GuardText[2].setPosition(view.getCenter().x, view.getCenter().y + 200); // center item for width, have the amount of string items + 1, so that they're equally spaced out


	for (int i = 0; i < guard_item_Number; i++) {
		window.draw(GuardText[i]);
	}



}

void guardDialogue::Up() {
	if (guardItemIndex - 1 >= 0) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		GuardText[guardItemIndex].setFillColor(sf::Color::Black); //set the blue color to white
		guardItemIndex--; //decrememnt the index
		GuardText[guardItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}

void guardDialogue::Down() {
	if (guardItemIndex + 1 < guard_item_Number) { // If the item index is above 0, so you cant just keep pressing up and break stuff
		GuardText[guardItemIndex].setFillColor(sf::Color::Black); //set the blue color to white
		guardItemIndex++; // increment the index
		GuardText[guardItemIndex].setFillColor(sf::Color::Blue); //set the white colour to blue
	}
}

void guardDialogue::Talk(sf::View &view, sf::RenderWindow &window) {
	if (!cancelTexture.loadFromFile("../assets/image_assets/cancelButton.png")) {
		std::cout << "Load fail Error on playerFaceTexture" << std::endl;
		system("pause");
	}

	cancelButton.setSize(sf::Vector2f(25, 25));
	cancelButton.setTexture(&cancelTexture);
	cancelButton.setPosition(view.getCenter().x + 155, view.getCenter().y + 240);

	
	std::vector<sf::Text>  talking(7, sf::Text(TalkDialogue)); // an array of 5 cell doorsa

	talking[0].setString("Sometimes I hate this job. others, I really like it");
	talking[1].setString("Hey man, I'm more ganster than you");
	talking[2].setString("The food in chow is like 40% cardboard");
	talking[3].setString("Get out of my face.");
	talking[4].setString("If you don't leave me alone, you're getting a charge!");
	talking[5].setString("Your girlfriends probably out there with Jodie");
	talking[6].setString("Protect them Junies in the shower");

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

void guardDialogue::Snitch(sf::View &view, sf::RenderWindow &window){
	std::vector<sf::Text>  snitching(4, sf::Text(TalkDialogue)); // an array of 5 cell doorsa

	snitching[0].setString("No information for guard");
	snitching[0].setPosition(view.getCenter().x - 100, view.getCenter().y + 90);
	snitching[1].setString("Guard: Get out of here, punk!");
	snitching[1].setPosition(view.getCenter().x - 100, view.getCenter().y + 140);

	snitching[2].setPosition(view.getCenter().x - 100, view.getCenter().y + 90);
	snitching[2].setString("You give the information to the guard");
	snitching[3].setPosition(view.getCenter().x - 100, view.getCenter().y + 140);
	snitching[3].setString("Guard: Nice Work!");


	for (int i = 0; i < snitching.size(); i++) {
		snitching[i].setFont(font);
		snitching[i].setCharacterSize(40);
		snitching[i].setFillColor(sf::Color(0, 0, 0));
		
	}
	if (prisonInfo == 0) {
		window.draw(snitching[0]);
		window.draw(snitching[1]);
	}
	else if (prisonInfo >= 1) {
		window.draw(snitching[2]);
		window.draw(snitching[3]);
		prisonInfo = 0;
	}

}

void guardDialogue::Mission(sf::View &view, sf::RenderWindow &window){
	
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

	std::vector<sf::Text>  guardmissions(7, sf::Text(missionDialogue)); // an array of 5 cell doorsa

	guardmissions[0].setString(GM1);
	guardmissions[1].setString(GM2);
	guardmissions[2].setString(GM3);
	guardmissions[3].setString(GM4);
	guardmissions[4].setString(GM5);
	guardmissions[5].setString(GM6);
	guardmissions[6].setString(GM7);

	for (int i = 0; i < guardmissions.size(); i++) {
		guardmissions[i].setFont(font);
		guardmissions[i].setCharacterSize(40);
		guardmissions[i].setFillColor(sf::Color(0, 0, 0));
		guardmissions[i].setPosition(view.getCenter().x - 170, view.getCenter().y + 90);
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		std::cout << "Mission Accepted" << std::endl; // use this for trade functionality later, give positive rep to player for accepting
		guardDState = guardDialogueMenu;
		dialogueCheck = false;
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		std::cout << "Mission Declined" << std::endl; // use this for trade functionality later,give negative rep to player for declining
		guardDState = guardDialogueMenu;
		dialogueCheck = false;
	}

	if (missionsInt == 0) { window.draw(guardmissions[0]); }
	else if (missionsInt == 1) { window.draw(guardmissions[1]); }
	else if (missionsInt == 2) { window.draw(guardmissions[2]); }
	else if (missionsInt == 3) { window.draw(guardmissions[3]); }
	else if (missionsInt == 4) { window.draw(guardmissions[4]); }
	else if (missionsInt == 5) { window.draw(guardmissions[5]); }
	else if (missionsInt == 6) { window.draw(guardmissions[6]); }


	window.draw(acceptButton);
	window.draw(declineButton);
}

void guardDialogue::dialogueHandler(sf::View &view, sf::RenderWindow &window, HUD &hud) {
		

		if (guardDState == guardDialogueMenu) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				Up();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				Down();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				switch (GetPressedItem()) {
				case 0: std::cout << "Talk" << std::endl;
						hud.guardRep += 2;
						guardDState = guardTalk; // setting the state to guard talk
						talkInt = rand() % 6;
					
					break;
				case 1: std::cout << "Snitch" << std::endl;
					if (hud.guardRep > 30) {
						hud.prisonerRep -= 10;
						hud.guardRep += 5;
					guardDState = snitching; // setting the state to snitching
					hud.guardRep += 10;
					}
					else {
						std::cout << "You need at least 20 guard rep to do this" << std::endl;
					}
					break;
				case 2: std::cout << "Missions" << std::endl;
					if (hud.guardRep > 60) {
						hud.guardRep += 7;
						hud.prisonerRep -= 7;
						guardDState = guardMissions; //setting the state to guard missions
						missionsInt = rand() % 6;
					}
					else {
						std::cout << "You need 40 guard rep to do this" << std::endl;
					}
					break;

				}
			}
		}

		if (guardDState == guardDialogueMenu) {
			drawDialogueBox(view, window);
			draw(view, window);

		}

		//GUARD___________________________________________________
		if (guardDState == guardTalk) {
			drawDialogueBox(view, window);
			Talk(view, window);

		}
		if (guardDState == snitching) {
			drawDialogueBox(view, window);
			Snitch(view, window);

		}
		if (guardDState == guardMissions) {
			drawDialogueBox(view, window);
			Mission(view, window);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			guardDState = guardDialogueMenu;
			dialogueCheck = false;
		}
	
}