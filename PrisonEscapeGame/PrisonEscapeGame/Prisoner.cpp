#include "Prisoner.h"
#include <iostream>
#include "Player.h"


std::string prisonerfilename = "file.txt";
int prisonerNumber;
std::stringstream pss;
std::string ps;
std::string prisonerPath;

enum PrisonerDir { Down, Right, Up, Left, Idle };
std::vector<PrisonerDir> lastPrisonerPosition;
std::vector<sf::Vector2i>PrisonAnim;

//sf::Vector2i PrisonAnim(1, Down);

Prisoner::Prisoner(std::string prisonerFile, sf::RenderWindow &window)
{
	PState = IDLE;
	for (int i = 0; i < lastPrisonerPosition.size(); i++) {
		lastPrisonerPosition[i] = Down;
		PrisonAnim[i].x = 1;
		PrisonAnim[i].y = Down;
	}
	std::ifstream myInputFile;
	myInputFile.open(prisonerFile, std::ios_base::in);
	if (myInputFile.is_open())
	{
		//read the first line which has the number of elements
		std::getline(myInputFile, ps);
		pss.str(ps);
		pss.ignore(21);
		pss >> prisonerNumber;
		prisoners.resize(prisonerNumber);
		prisonerTexture.resize(prisonerNumber);

		pss.clear();


		float sizeX, sizeY;

		for (int i = 0; i < prisonerNumber; i++)
		{

			//NAME AND NUMBER
			//POSITION
			//SIZE

			//TEXTURE
			getline(myInputFile, ps);
			pss.clear();
			pss.str(ps);
			getline(myInputFile, ps);
			pss.clear();
			pss.str(ps);
			pss >> prisonerX >> prisonerY;
			getline(myInputFile, ps);
			pss.clear();
			pss.str(ps);
			pss >> sizeX >> sizeY;
			getline(myInputFile, ps);
			pss.clear();
			pss.str(ps);
			pss >> prisonerPath;

			sf::Vector2i pos(prisonerX, prisonerY);
			sf::Vector2f size(sizeX, sizeY);


			if (!prisonerTexture[i].loadFromFile(prisonerPath)) {
				std::cout << "Load fail Error on prisonerTexture" << std::endl;
				system("pause");
			}


			prisoners[i].setPosition(pos.x, pos.y);
			prisoners[i].setOrigin(size / 2.0f);
			prisoners[i].setSize(size);
			prisoners[i].setTexture(&prisonerTexture[i]);


		}
	}
}

Prisoner::~Prisoner()
{
}



void Prisoner::CollisionResponse(int prisonerNum)
{
		prisoners[prisonerNum].move(lastVelocity[prisonChoice]);
}



void Prisoner::drawPrisoner(sf::RenderWindow &window, HUD &hud, Player &player) {
	
	PrisonAnim.resize(prisoners.size());
	lastPrisonerPosition.resize(prisoners.size());
	vel.resize(prisoners.size());
	lastVelocity.resize(prisoners.size());

	sf::Vector2i chowWaypoint(90, 1620); // chow time
	sf::Vector2i workWaypoint(1680, 2520); // work time
	sf::Vector2i showerWaypoint(64, 64); // shower time
	sf::Vector2i yardWaypoint(90, 2520); // shower time
	sf::Vector2i freeWaypoint(1600, 1600); // free time area waypoint
	if (hud.yardTime == true) {
		std::cout << "YardTime" << std::endl;
		wayPoint.x = yardWaypoint.x;
		wayPoint.y = yardWaypoint.y;
	}
	if (hud.chowTime == true) {
		std::cout << "chowTime" << std::endl;
		wayPoint.x = chowWaypoint.y;
		wayPoint.y = chowWaypoint.y;
	}
	if (hud.showerTime == true) {
		std::cout << "showerTime" << std::endl;
		wayPoint.x = showerWaypoint.x;
		wayPoint.y = showerWaypoint.y;
	}
	if (hud.workTime == true) {
		std::cout << "workTime" << std::endl;
		wayPoint.x = workWaypoint.x;
		wayPoint.y = workWaypoint.y;
	}
	if (hud.freeTime == true) {
		std::cout << "freeTime" << std::endl;
		wayPoint.x = freeWaypoint.x;
		wayPoint.y = freeWaypoint.y;
	}
	if (hud.bedTime == true) {

	}

	if (PState == IDLE) { // if the prisoner state is idle, the prisoners will wander by calling the wandering function
		Wandering(hud);
		std::cout << "Prisoner State == Wandering" << std::endl;
	}
	if (PState == prisonerAngry) { // if the prisoner state is set to angry, the function will be called to make the prisoner attack
		prisonerAttack(player);
		std::cout << "Prisoner State == Attacking" << std::endl;
	}
	if(PState == PathFollow) { // if the prisoner is not angry or idle, the prisoner should be checking to follow the path
		//pathFollowing(hud);
		std::cout << "Prisoner State == PathFollowing" << std::endl;
	}

	for (int i = 0; i < prisoners.size(); i++) {
		for (int j = 0; j < prisonerTexture.size(); j++) {
			PrisonAnim[i].x++;
			if (PrisonAnim[i].x * 32 >= prisonerTexture[j].getSize().x) { // once the sprite reaches the end of the sprite sheet, reset to 0 again
				PrisonAnim[i].x = 0;
			}
		}
		prisoners[i].setTextureRect(sf::IntRect(PrisonAnim[i].x * 32, PrisonAnim[i].y * 32, 32, 32)); // cropping the image with the position and size of the image 

		window.draw(prisoners[i]);
	}

		

	if (prisonerAttacked == true) {
		PState = prisonerAngry;
	}


}


void Prisoner::Wandering(HUD &hud) {
	std::string SecondsString = std::to_string(prisonTime);
	sf::Time TimeElapsed = PrisonClock.getElapsedTime(); // setting the time to the hud clock, so it can count seconds
	sf::Time seconds = sf::seconds(1); // this is to compare to the time elapsed to get 1 second

	if (TimeElapsed >= seconds) { // if the time elapsed is a second, increment the HUDTime and restart the HUDClock 
		prisonTime++;
		PrisonClock.restart();
		std::cout << "Prisoner Time: "<< prisonTime << std::endl;
	}

	if (prisonTime >= 5) { // if the prisonTime exceeds this, move the prisoner, update the random numbers for direction and prisoner selected
		prisonRand = rand() % 4 + 1; // choosing a direction, either 1, 2, 3 or 4 to move in 
		prisonChoice = rand() % prisoners.size(); // generating a random number, depending on how many prisoners there are, and choosing which prisoner to move
		std::cout << "Random prisoner choice: " << prisonChoice << std::endl;
		prisonTime = 0; //setting prison Time back to 0
	}
	
	if (prisonRand == 1) {
	//	std::cout << "Prison Direction choice left(1)" << std::endl;
		
				vel[prisonChoice].x -= moveSpeed;
				PrisonAnim[prisonChoice].y = Left;
				lastPrisonerPosition[prisonChoice] = Left;
				
	}
	else if (prisonRand == 2) {
	//	std::cout << "Prison Direction choice right(2)" << std::endl;
				vel[prisonChoice].x += moveSpeed;
				PrisonAnim[prisonChoice].y = Right;
				lastPrisonerPosition[prisonChoice] = Right;
			
	}
	else if (prisonRand == 3) {
	//	std::cout << "Prison Direction choice up(3)" << std::endl;
				vel[prisonChoice].y -= moveSpeed;
				PrisonAnim[prisonChoice].y = Up;
				lastPrisonerPosition[prisonChoice] = Up;
			
	}
	else {
	//	std::cout << "Prison Direction choice down(4)" << std::endl;
				vel[prisonChoice].y += moveSpeed;
				PrisonAnim[prisonChoice].y = Down;
				lastPrisonerPosition[prisonChoice] = Down;
				
	}

	prisoners[prisonChoice].move(vel[prisonChoice].x, vel[prisonChoice].y);
	lastVelocity[prisonChoice] = sf::Vector2f(-vel[prisonChoice].x, -vel[prisonChoice].y);



	if (wayPoint.x != 0 && wayPoint.y != 0) { // if the waypoint updates (not bedTime, follow the path)
		std::cout << "State change to path following" << std::endl;
		PState = PathFollow;
	}

	}




//void Prisoner::pathFollowing(HUD &hud) {
//	if (wayPoint.x != 0 || wayPoint.y != 0) {
//		for (int i = 0; i < prisoners.size(); i++) {
//			if (prisoners[i].getPosition().x < wayPoint.x +(i * 32)) { // if the prisoners x position is less than the waypoints x position, move positively in the X direction
//				vel.x += moveSpeed;
//				PrisonAnim[i].y = Right;
//				lastPrisonerPosition[i] = Right;
//			}
//			else if (prisoners[i].getPosition().x > wayPoint.x) {
//				vel.x -= moveSpeed;
//				PrisonAnim[i].y = Left;
//				lastPrisonerPosition[i] = Left;
//			}
//
//
//			if (prisoners[i].getPosition().y < wayPoint.y) { // if the prisoners Y position is less than the waypoints Y position, move positively in the Y direction
//				vel.y -= moveSpeed;
//				PrisonAnim[i].y = Up;
//				lastPrisonerPosition[i] = Up;
//			}
//			else if (prisoners[i].getPosition().y > wayPoint.y) {
//				vel.y += moveSpeed;
//				PrisonAnim[i].y = Down;
//				lastPrisonerPosition[i] = Down;
//			}
//			if (prisoners[i].getPosition().x == wayPoint.x + (i * 32) && prisoners[i].getPosition().y == wayPoint.y) {
//				PState = IDLE;
//			}
//
//		}
//	}
//
//
//	for (int i = 0; i < prisoners.size(); i++) {
//		prisoners[i].move(vel.x, vel.y);
//		lastVelocity = sf::Vector2f(-vel.x, -vel.y);
//	}
//
//	std::string wayPointStringX = std::to_string(wayPoint.x);
//	std::string wayPointStringY = std::to_string(wayPoint.y);
//	std::cout << "Waypoint position X: " << wayPointStringX << ", Waypoint position Y: "  << wayPointStringY << std::endl;
//	/*
//	704 192 - prisoner 1
//	1024 192 - prisoner 2
//	1344 192 - prisoner 3
//	1664 192 - prisoner 4
//	*/
//
//
//}
//
	
	void Prisoner::PrisonerAttackedChoice(int &prisoner) {
		std::cout << "Prisoner Attacked: " << prisoner << std::endl;
		PrisonNumAngry = prisoner;
		std::cout << "Prisoner Angry = " << PrisonNumAngry << std::endl;
	}
	

	void Prisoner::prisonerAttack(Player &player) {
		if (&prisoners[PrisonNumAngry].getPosition().x >= &player.characterSprite.getPosition().x) {
			vel[PrisonNumAngry].x -= moveSpeed;
			PrisonAnim[PrisonNumAngry].y = Left;
			lastPrisonerPosition[PrisonNumAngry] = Left;
		}
		else if (&prisoners[PrisonNumAngry].getPosition().x <= &player.characterSprite.getPosition().x + 32) {
			vel[PrisonNumAngry].x += moveSpeed;
			PrisonAnim[PrisonNumAngry].y = Right;
			lastPrisonerPosition[PrisonNumAngry] = Right;
		}
		else if (&prisoners[PrisonNumAngry].getPosition().y >= &player.characterSprite.getPosition().y) {
			vel[PrisonNumAngry].y -= moveSpeed;
			PrisonAnim[PrisonNumAngry].y = Up;
			lastPrisonerPosition[PrisonNumAngry] = Up;
		}
		else if(&prisoners[PrisonNumAngry].getPosition().y <= &player.characterSprite.getPosition().y + 32){
			vel[PrisonNumAngry].y += moveSpeed;
			PrisonAnim[PrisonNumAngry].y = Down;
			lastPrisonerPosition[PrisonNumAngry] = Down;
		}

		prisoners[PrisonNumAngry].move(vel[PrisonNumAngry].x, vel[PrisonNumAngry].y); // making the prisoner follow the player 
		lastVelocity[PrisonNumAngry] = sf::Vector2f(-vel[PrisonNumAngry].x, -vel[PrisonNumAngry].y);
		

		//If the prisoner is within a 300 pixel range to the player, the prisoner can follow the player, else go back to wandering - add reduction to prisoner rep later
		if (&prisoners[PrisonNumAngry].getPosition().x < &player.characterSprite.getPosition().x - 192 || &prisoners[PrisonNumAngry].getPosition().x > &player.characterSprite.getPosition().x + 192) {
			if (&prisoners[PrisonNumAngry].getPosition().y < &player.characterSprite.getPosition().y - 192 || &prisoners[PrisonNumAngry].getPosition().y > &player.characterSprite.getPosition().y + 192) {
				std::cout << "Player out of range" << std::endl;
				PState = IDLE;
			}
		}
}

void Prisoner::prisonerState() {

}


