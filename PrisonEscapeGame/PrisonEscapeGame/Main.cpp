#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <cstdlib>
#include "Background.h"
#include "HUD.h"
#include "Menu.h"
#include "SkillMenu.h"
#include "SkillItems.h"
#include "OptionsMenu.h"
#include "Instructions.h"
#include "Player.h"
#include "Prisoner.h"
#include "Guard.h"
#include "Warden.h"
#include "Nurse.h"
#include "mapLoader.h"
#include "Furniture.h"
#include "prisonWalls.h"
#include "Doors.h"
#include "furnitureInv.h"
#include "prisonerDialogue.h"
#include "guardDialogue.h"
#include "SFX.h"
#include "InventoryItems.h"

/*TODO - 

Mouse Handler: Implement Mouse Input on Instructions Menu and fix mouse and key input skipping menu's 
On Key/Mouse Input: Fix error with changing state


HUDItems: Finish the Instructions Menu, Crafting menu needs to be implemented, MouseHander for HUDItems, including start menu
Objects: Make Skill Item furniture increment skill on use
AI: Path Finding Algorithm A* - Use on all characters, use the given states in the class to change their behavior
*/


enum GameState { StartMenu, SkillsMenu, Options, Game, InstructionsMenu };
enum InvState {LockerInv,  BinInv, FtLockerInv, DeskInv, TlsCbInv, DumpsterInv, noState};
enum skillItemsMenu { weightsMenu, bikeMenu, bookshelfMenu, noMenu };
int GameState = StartMenu;

float musicVolume;

sf::Vector2i ScreenSize(800, 600);
sf::Vector2f pos(ScreenSize.x / 2, ScreenSize.y / 2); // halving the screen size to set the centre of screen as the movement position

int main()
{
	sf::SoundBuffer soundBuffer; // sound buffer
	sf::Music menuMusic; // backgroundMusic
	sf::Clock clock;
	sf::View view; //setting the view for the scrolling screen
	sf::Vector2f playerStartPos(100.0f, 100.f);
	sf::Vector2i ScreenSize(800, 600);
	sf::Vector2f direction;
	sf::RenderWindow window(sf::VideoMode(ScreenSize.x, ScreenSize.y), "Prison Escape Game");
	

	InvState invS;
	skillItemsMenu skills;

	mapLoader map;
	prisonerDialogue prisonD;
	guardDialogue guardD;
	HUD hud;
	SFX sfx;
	furnitureInv furninv;

	//MENU'S
	Menu menu(window.getSize().x, window.getSize().y); // creating the start menu
	OptionsMenu options(window.getSize().x, window.getSize().y); // crating the options menu 
	Instructions instructions(window.getSize().x, window.getSize().y); 
	SkillMenu skillmenu(window.getSize().x, window.getSize().y); // creating the Skill menu

	//Loading in Menu music
	if (!menuMusic.openFromFile("../assets/sound_assets/Music/BlueHighway.ogg")) { 
		std::cout << "Background music not loaded" << std::endl;
		return -1;
	}

	//Text Assets(filepaths) to be loaded in
	std::string wallFile("../assets/text_assets/Walls.txt");
	std::string doorFile("../assets/text_assets/Doors.txt");
	std::string furnitureFile("../assets/text_assets/Furniture.txt");
	std::string skillsFile("../assets/text_assets/SkillItems.txt");
	std::string prisonerFile("../assets/text_assets/prisoners.txt");
	std::string guardFile("../assets/text_assets/guards.txt");
	std::string nurseFile("../assets/text_assets/nurses.txt");
	std::string wardenFile("../assets/text_assets/warden.txt");

	std::string inventoryFile("../assets/text_assets/InventoryItems.txt");
	
	

	//Image Assets to be loaded in
	Background background("../assets/image_assets/Background.png");
	Background background2("../assets/image_assets/Background2.png");
	Background SkillsBackground("../assets/image_assets/SkillsMenuBackground.png");
	Background OptionsBackground("../assets/image_assets/OptionsBackground.png");
	Background InstructionsBackground("../assets/image_assets/InstructionsBackground.png");
	
	//Collidable Furniture
	Doors doors(doorFile, window);
	Furniture furniture(furnitureFile, window);
	prisonWalls walls(wallFile, window);
	SkillItems skillitems(skillsFile, window);


	//Characters (player and AI)
	Player player(sf::Vector2f(32,32), sf::Vector2f(150, 150));
	Prisoner prisoner(prisonerFile, window);
	Guard guard(guardFile, window);
	Warden warden(wardenFile, window);
	Nurse nurse(nurseFile, window);
	InventoryItems invItems(inventoryFile, window);


	invS = noState;
	skills = noMenu;

	
	menuMusic.play(); // play the menu music
	menuMusic.getLoop();
	
	
	view.reset(sf::FloatRect(0, 0, ScreenSize.x, ScreenSize.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f)); // from the left point(start point to width scale), top(start to screen height scale), screen width scale, screen height scale
	view.zoom(1.0f); // zooming out - FOR DEBUG

	while (window.isOpen())
	{
		// use window events for keyboard input, so that the gamestates dont switch
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				exit(1); // exiting the program if the close button is pressed
				break;
			case sf::Event::KeyPressed:
				if (GameState == StartMenu) {
					menu.KeyHandler();
				}
				else if (GameState == SkillsMenu) {
					skillmenu.keyHandler(hud);
				
				}
				else if (GameState == Options) {
					options.keyHandler();
				
				}
				else if (GameState == InstructionsMenu) {
					instructions.keyHandler();
				
				}
				else if (GameState == Game) {
					hud.HUDUserInput(view, window);
				}
				
				break;
			case sf::Event::MouseButtonPressed:
				if (GameState == StartMenu) {
					menu.MouseHandler(window);
				}
				else if (GameState == SkillsMenu) {
					skillmenu.mouseHandler(window);
				}
				else if (GameState == Options) {
					options.mouseHandler(window);
				}
				else if (GameState == InstructionsMenu) {
					instructions.mouseHandler(window);
				}
				else if (GameState == Game) {
					hud.MouseInput(window);
				}
				break;
			}
		}
			//COLLISION
		if(GameState == Game){
			for (int i = 0; i < walls.Walls.size(); i++) {
				if (player.characterSprite.getGlobalBounds().intersects(walls.Walls[i].getGlobalBounds())) {
					std::cout << "player Collision made with wall: " << i << std::endl;
					player.CollisionResponse(); // stops player movement
					sfx.collisionEffect(options);
				}
				for (int j = 0; j < prisoner.prisoners.size(); j++) {
					if (prisoner.prisoners[j].getGlobalBounds().intersects(walls.Walls[i].getGlobalBounds())) {
						std::cout << "prisoner Collision made with wall: " << i << std::endl;
						prisoner.CollisionResponse(); // stops player movement
						
					}
				}
				for (int j = 0; j < guard.guards.size(); j++) {
					if (guard.guards[j].getGlobalBounds().intersects(walls.Walls[i].getGlobalBounds())) {
						std::cout << "guard Collision made with wall: " << i << std::endl;
						guard.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < nurse.nurses.size(); j++) {
					if (nurse.nurses[j].getGlobalBounds().intersects(walls.Walls[i].getGlobalBounds())) {
						std::cout << "nurse Collision made with wall: " << i << std::endl;
						nurse.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < warden.Wardens.size(); j++) {
					if (warden.Wardens[j].getGlobalBounds().intersects(walls.Walls[i].getGlobalBounds())) {
						std::cout << "warden Collision made with wall: " << i << std::endl;
						warden.CollisionResponse(); // stops player movement

					}
				}
			}
			for (int i = 0; i < skillitems.skillItems.size(); i++) {
				if (player.characterSprite.getGlobalBounds().intersects(skillitems.skillItems[i].getGlobalBounds())) {
					std::cout << "Collision made with SkillItem: " << i << std::endl;
					player.CollisionResponse(); // stops player movement
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						if (i <= 5) {
							std::cout << "Interaction made with bike" << std::endl;
							skills = bikeMenu;
						}
						if (i >= 6 && i <= 11) {
							std::cout << "Interaction made with Weights Bench" << std::endl;
							skills = weightsMenu;
						}
						else if (i >= 12 && i <= 28) {
							std::cout << "Interaction made with bookshelf" << std::endl;
							skills = bookshelfMenu;
						}
					}
				}
				for (int j = 0; j < prisoner.prisoners.size(); j++) {
					if (prisoner.prisoners[j].getGlobalBounds().intersects(skillitems.skillItems[i].getGlobalBounds())) {
						std::cout << "prisoner Collision made with skill item: " << i << std::endl;
						prisoner.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < guard.guards.size(); j++) {
					if (guard.guards[j].getGlobalBounds().intersects(skillitems.skillItems[i].getGlobalBounds())) {
						std::cout << "guard Collision made with skill item: " << i << std::endl;
						guard.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < nurse.nurses.size(); j++) {
					if (nurse.nurses[j].getGlobalBounds().intersects(skillitems.skillItems[i].getGlobalBounds())) {
						std::cout << "nurse Collision made with skill item: " << i << std::endl;
						nurse.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < warden.Wardens.size(); j++) {
					if (warden.Wardens[j].getGlobalBounds().intersects(skillitems.skillItems[i].getGlobalBounds())) {
						std::cout << "warden Collision made with skill item: " << i << std::endl;
						warden.CollisionResponse(); // stops player movement
						
					}
				}
			}

			for (int i = 0; i < doors.doors.size(); i++) {
				if (player.characterSprite.getGlobalBounds().intersects(doors.doors[i].getGlobalBounds())) {
					std::cout << "Collision made with door: " << i << std::endl;
					player.CollisionResponse();// stops player movement
					sfx.openDoorEffect(options);
					
					if (doors.doors[i].getRotation() == 90) { // if the door is at a 90 degree angle, move it down if not move it right
							
								doors.doors[i].move(sf::Vector2f(0, 64));
							
						} else {
								doors.doors[i].move(sf::Vector2f(64, 0));
					}
				}
				for (int j = 0; j < prisoner.prisoners.size(); j++) {
					if (prisoner.prisoners[j].getGlobalBounds().intersects(doors.doors[i].getGlobalBounds())) {
						std::cout << "prisoner Collision made with door: " << i << std::endl;
						prisoner.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < guard.guards.size(); j++) {
					if (guard.guards[j].getGlobalBounds().intersects(doors.doors[i].getGlobalBounds())) {
						std::cout << "guard Collision made with door: " << i << std::endl;
						guard.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < nurse.nurses.size(); j++) {
					if (nurse.nurses[j].getGlobalBounds().intersects(doors.doors[i].getGlobalBounds())) {
						std::cout << "nurse Collision made with door: " << i << std::endl;
						nurse.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < warden.Wardens.size(); j++) {
					if (warden.Wardens[j].getGlobalBounds().intersects(doors.doors[i].getGlobalBounds())) {
						std::cout << "warden Collision made with door: " << i << std::endl;
						warden.CollisionResponse(); // stops player movement

					}
				}

			}

			for (int i = 0; i < furniture.furniture.size(); i++) {
				if (player.characterSprite.getGlobalBounds().intersects(furniture.furniture[i].getGlobalBounds())) {
				//	std::cout << "Collision made with piece of furniture: " << i << std::endl;
					player.CollisionResponse();// stops player movement

					if (i >= 18 && i <= 27) { if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						std::cout << "Accessed Locker - code Number: " << i << std::endl;
						invS = LockerInv;
					
					} }
					if (i >= 28 && i <= 38) { if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						std::cout << "Accessed Bin - code Number: "  << i << std::endl;
						invS = BinInv;
					
					} }
					if (i >= 69 && i <= 73) { if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						std::cout << "Accessed Footlocker - code Number: "  << i << std::endl;
						invS = FtLockerInv;
					
					} }
					if (i >= 89 && i <= 95) { if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						std::cout << "Accessed Desk - code Number: " << i << std::endl;
						invS = DeskInv;
				
					} }
					if (i >= 133 && i <= 134) { if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						std::cout << "Accessed ToolsCabinet - code Number: "  << i << std::endl;
						invS = TlsCbInv;

					} }
					if (i >= 137 && i <= 138) { if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						std::cout << "Accessed Dumpster - code Number: "  << i << std::endl;
						invS = DumpsterInv;
						
					} }

				}
				for (int j = 0; j < prisoner.prisoners.size(); j++) {
					if (prisoner.prisoners[j].getGlobalBounds().intersects(furniture.furniture[i].getGlobalBounds())) {
						std::cout << "prisoner Collision made with furniture piece: " << i << std::endl;
						prisoner.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < guard.guards.size(); j++) {
					if (guard.guards[j].getGlobalBounds().intersects(furniture.furniture[i].getGlobalBounds())) {
						std::cout << "guard Collision made with furniture piece: " << i << std::endl;
						guard.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < nurse.nurses.size(); j++) {
					if (nurse.nurses[j].getGlobalBounds().intersects(furniture.furniture[i].getGlobalBounds())) {
						std::cout << "nurse Collision made with furniture piece: " << i << std::endl;
						nurse.CollisionResponse(); // stops player movement

					}
				}
				for (int j = 0; j < warden.Wardens.size(); j++) {
					if (warden.Wardens[j].getGlobalBounds().intersects(furniture.furniture[i].getGlobalBounds())) {
						std::cout << "warden Collision made with furniture piece: " << i << std::endl;
						warden.CollisionResponse(); // stops player movement

					}
				}
			}

			for (int i = 0; i < prisoner.prisoners.size(); i++) {
				if (player.characterSprite.getGlobalBounds().intersects(prisoner.prisoners[i].getGlobalBounds())) {
					player.CollisionResponse();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
						prisonD.dialogueCheck = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						std::cout << "prisoner Hit" << std::endl;
						prisoner.prisonerAttacked = true;
						prisoner.prisonerHealth -= 10; // temporary value until strength and skills are implemented
						hud.prisonerRep -= 10;
						sfx.punchEffect(options);
					}
				}
				else {
					prisoner.PState == IDLE; // making the prisoner go back to idle after interaction
				}
			}
			for (int i = 0; i < guard.guards.size(); i++) {
				if (player.characterSprite.getGlobalBounds().intersects(guard.guards[i].getGlobalBounds())) {
						player.CollisionResponse();

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
							guardD.dialogueCheck = true;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
							guard.guardHealth -= 10; // temporary value until strength and skills are implemented
							hud.guardRep -= 10;
							sfx.punchEffect(options);
						}
					}
					else {
						guard.GState == guardIDLE;// making the guard go back to idle after interaction
					}
				}
			for (int i = 0; i < warden.Wardens.size(); i++) {
				if (player.characterSprite.getGlobalBounds().intersects(warden.Wardens[i].getGlobalBounds())) {
					player.CollisionResponse();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						warden.WardenHealth -= 10;  // temporary value until strength and skills are implemented
						hud.guardRep -= 1;
						sfx.punchEffect(options);
					}
				}
			}
			for (int i = 0; i < nurse.nurses.size(); i++) {
				if (player.characterSprite.getGlobalBounds().intersects(nurse.nurses[i].getGlobalBounds())) {
					player.CollisionResponse();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						nurse.NurseHealth -= 10;
						hud.guardRep -= 1;
						sfx.punchEffect(options);
					}
				}
			}
		} // end of gamestate game

		

		

		if (player.characterSprite.getPosition().x + 16 > ScreenSize.x / 2 + 16) {  // if the the player sprite with added amount gets beyond half the screen size, stop moving the player
			pos.x = player.characterSprite.getPosition().x + 16;
		}
		else {
			pos.x = ScreenSize.x / 2;
		}
		if (player.characterSprite.getPosition().y + 16 > ScreenSize.y / 2 + 16) {// if the the player sprite with added amount gets beyond half the screen size, stop moving the player
			pos.y = player.characterSprite.getPosition().y + 16;
		}
		else {
			pos.y = ScreenSize.y / 2;
		}

		window.clear(sf::Color(0, 0, 0));
			view.setCenter(pos); 
		window.setView(view); // setting the view

		
		if (GameState == StartMenu) {
			int LightFlicker = rand() % 10;
			for (int x = 1; x < 256; x++) {
				int LightFlicker = rand() % 10; // flickering the light only slightly, by having random number generator
			}
			if (LightFlicker == 8) { // if the value is 8, paint the background with the background with no lighting
				background2.drawBackground(window);
			}
			else {
				background.drawBackground(window); // if not paint the light background
			}
			if (menu.playPressed == true) {
				menu.playPressed = false;
				GameState = SkillsMenu;
			}
			if (menu.optionsPressed == true) {
				menu.optionsPressed = false;
				GameState = Options;
			}
			if (menu.exitPressed == true) {
				window.close();
			}
			menu.draw(window);	
		}
	
		if (GameState == Options) {
			if (options.instrucPress == true) {
				options.instrucPress = false;
				GameState = InstructionsMenu;
			}
			if (options.backPress == true) {
				options.backPress = false;
				GameState = StartMenu;
			}
			
			OptionsBackground.drawBackground(window);
			options.draw(window);
			options.drawBars(window);

			musicVolume = options.Music;
			menuMusic.setVolume(musicVolume);
			
			
		
		}

		if (GameState == InstructionsMenu) {
			if (instructions.backPress == true) {
				instructions.backPress = false;
				GameState = Options;
			}
			InstructionsBackground.drawBackground(window);
			instructions.draw(window);
		}
		
		if (GameState == SkillsMenu) {
			if (skillmenu.exitPress == true) {
				skillmenu.exitPress = false;
				GameState = StartMenu;
			}
			if (skillmenu.gamePress == true) {
				skillmenu.gamePress = false;
				GameState = Game;
			}
			SkillsBackground.drawBackground(window);
			skillmenu.drawBars(window, hud);
			skillmenu.draw(window);	
		}

	
		//drawing 
		if (GameState == Game)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) { // simple button click to close all states
				invS = noState;
				skills = noMenu;
			}
			menuMusic.pause(); // pause that funky music
		//	background.drawBackground(window);
			map.drawMap(window);

			//drawing the walls
			walls.drawWalls(window);
			furniture.drawFurniture(window);
			doors.drawDoors(window);
			skillitems.drawSkillItems(window);
			
			player.playerKeyboardMovement(view, window);
			
			
	

			if (invS == LockerInv) {  furninv.drawLocker(view, window, hud);  }
			else if (invS == BinInv) { furninv.drawBin(view, window, hud); }
			else if (invS == FtLockerInv) { furninv.drawFootLocker(view, window, hud); }
			else if (invS == DeskInv) { furninv.drawDesk(view, window, hud); }
			else if (invS == TlsCbInv) { furninv.drawToolsCabinet(view, window, hud); }
			else if (invS == DumpsterInv) { furninv.drawBigBin(view, window, hud); }
			

			if (skills == bookshelfMenu) { // if the bookshelf is accessed, open up the skills item hud and increase knowledge by playing minigame (not yet implemented)
				skillitems.knowledgeIncrease(window, view, hud);
			}
			else if (skills == bikeMenu) { // if the bike is accessed, open up the skills item hud and increase knowledge by playing minigame (not yet implemented)
				skillitems.staminaIncrease(window, view, hud); 
			}
			else if (skills == weightsMenu) { // if the weights bench is accessed, open up the skills item hud and increase knowledge by playing minigame (not yet implemented)
				skillitems.strengthIncrease(window, view, hud);
			}
	

			prisoner.drawPrisoner(window, hud, player);
			warden.drawWarden(window);
			nurse.drawNurse(window);
			guard.drawGuard(window);
			
			hud.drawHUD(view, window);
			
		

			if (hud.SkilOpen == true) {
				hud.drawSkills(view, window);
			}
			if (hud.MisOpen == true) {
				hud.drawMissions(view, window);
			}
			if (hud.InvOpen == true) {
				hud.drawInventory(view, window);
			} if (hud.RepOpen == true) {
				hud.drawReputation(view, window);
			}
			if (hud.craftOpen == true) {
				hud.drawCraft(view, window);
			}

			if (prisonD.dialogueCheck == true) {
				prisonD.dialogueHandler(view, window, hud);
			}
			if (guardD.dialogueCheck == true) {
				guardD.dialogueHandler(view, window, hud);
			}
			
		}

	


	

	
		
		

		//displaying drawn stuff
		window.display();
	}

	return EXIT_SUCCESS;
}


// https://www.youtube.com/watch?v=ghgd-R1gRmc - 22:51 - 24/11/2017
// https://www.sfml-dev.org/tutorials/2.4/graphics-view.php - look at this for scrolling view screen
//https://www.youtube.com/watch?v=ma5QWDYsmBg - Spritesheet
//https://www.youtube.com/watch?v=SYrzeVEjRE0 - clock sprite movement

// http://freemusicarchive.org/curator/video - sound assets placeholder