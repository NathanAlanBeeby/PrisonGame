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
		//	std::cout << "Prisoner State == Wandering" << std::endl;
	}
	if (PState == prisonerAngry) { // if the prisoner state is set to angry, the function will be called to make the prisoner attack
		prisonerAttack(hud, player);
		//	std::cout << "Prisoner State == Attacking" << std::endl;
	}
	if (PState == PathFollow) { // if the prisoner is not angry or idle, the prisoner should be checking to follow the path
		pathFollowing(hud);
		//	std::cout << "Prisoner State == PathFollowing" << std::endl;
	}

	if (prisonerAttacked == true) {
		PState = prisonerAngry;
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

}


void Prisoner::Wandering(HUD &hud) {
	std::string SecondsString = std::to_string(prisonTime);
	sf::Time TimeElapsed = PrisonClock.getElapsedTime(); // setting the time to the hud clock, so it can count seconds
	sf::Time seconds = sf::seconds(1); // this is to compare to the time elapsed to get 1 second

	if (TimeElapsed >= seconds) { // if the time elapsed is a second, increment the HUDTime and restart the HUDClock 
		prisonTime++;
		PrisonClock.restart();
		//	std::cout << "Prisoner Time: "<< prisonTime << std::endl;
	}

	if (prisonTime >= 5) { // if the prisonTime exceeds this, move the prisoner, update the random numbers for direction and prisoner selected
		prisonRand = rand() % 4 + 1; // choosing a direction, either 1, 2, 3 or 4 to move in 
		prisonChoice = rand() % prisoners.size(); // generating a random number, depending on how many prisoners there are, and choosing which prisoner to move
	//	std::cout << "Random prisoner choice: " << prisonChoice << std::endl;
		prisonTime = 0; //setting prison Time back to 0
	}

	if (prisonRand == 1) {
		//	std::cout << "Prison Direction choice left(1)" << std::endl;

		vel[prisonChoice].x = -moveSpeed;
		PrisonAnim[prisonChoice].y = Left;
		lastPrisonerPosition[prisonChoice] = Left;

	}
	if (prisonRand == 2) {
		//	std::cout << "Prison Direction choice right(2)" << std::endl;
		vel[prisonChoice].x = moveSpeed;
		PrisonAnim[prisonChoice].y = Right;
		lastPrisonerPosition[prisonChoice] = Right;

	}
	if (prisonRand == 3) {
		//	std::cout << "Prison Direction choice up(3)" << std::endl;
		vel[prisonChoice].y = -moveSpeed;
		PrisonAnim[prisonChoice].y = Up;
		lastPrisonerPosition[prisonChoice] = Up;

	}
	if (prisonRand == 4) {
		//	std::cout << "Prison Direction choice down(4)" << std::endl;
		vel[prisonChoice].y = moveSpeed;
		PrisonAnim[prisonChoice].y = Down;
		lastPrisonerPosition[prisonChoice] = Down;

	}

	prisoners[prisonChoice].move(vel[prisonChoice].x, vel[prisonChoice].y);
	lastVelocity[prisonChoice] = sf::Vector2f(-vel[prisonChoice].x, -vel[prisonChoice].y);



	if (wayPoint.x != 0 && wayPoint.y != 0) { // if the waypoint updates (not bedTime, follow the path)
		//std::cout << "State change to path following" << std::endl;
		PState = PathFollow;
	}


}




void Prisoner::pathFollowing(HUD &hud) {
	std::cout << "WayPoint, X: " << wayPoint.x << ", Y: " << wayPoint.y << std::endl;

	if (wayPoint.x != 0 || wayPoint.y != 0) {
		for (int i = 0; i < prisoners.size(); i++) {
			//std::cout << "Prisoner Position: " << prisoners[i].getPosition().x << ", Y: " << prisoners[i].getPosition().y << std::endl;
			if (prisoners[i].getPosition().x < wayPoint.x + (i * 32)) { // if the prisoners x position is less than the waypoints x position, move positively in the X direction
				vel[i].x = moveSpeed;
				PrisonAnim[i].y = Right;
				lastPrisonerPosition[i] = Right;
			}
			if (prisoners[i].getPosition().x > wayPoint.x) {
				vel[i].x = -moveSpeed;
				PrisonAnim[i].y = Left;
				lastPrisonerPosition[i] = Left;
			}


			if (prisoners[i].getPosition().y > wayPoint.y) { // if the prisoners Y position is less than the waypoints Y position, move positively in the Y direction
				vel[i].y = -moveSpeed;
				PrisonAnim[i].y = Up;
				lastPrisonerPosition[i] = Up;
			}
			if (prisoners[i].getPosition().y < wayPoint.y) {
				vel[i].y = moveSpeed;
				PrisonAnim[i].y = Down;
				lastPrisonerPosition[i] = Down;
			}
			if (prisoners[i].getPosition().x == wayPoint.x + (i * 32) && prisoners[i].getPosition().y == wayPoint.y) {
				PState = IDLE;
			}
			prisoners[i].move(vel[i].x, vel[i].y);
			lastVelocity[i] = sf::Vector2f(-vel[i].x, -vel[i].y);
		}
	}

	/*
	704 192 - prisoner 1
	1024 192 - prisoner 2
	1344 192 - prisoner 3
	1664 192 - prisoner 4
	*/


}


void Prisoner::PrisonerAttackedChoice(int &prisoner) {
	PrisonNumAngry = prisoner;
}


void Prisoner::prisonerAttack(HUD &hud, Player &player) {
	if (prisoners[PrisonNumAngry].getPosition().x >= player.getPosition().x) {
		vel[PrisonNumAngry].x = -moveSpeed;
		PrisonAnim[PrisonNumAngry].y = Left;
		lastPrisonerPosition[PrisonNumAngry] = Left;
	}
	if (prisoners[PrisonNumAngry].getPosition().x <= player.getPosition().x + 32) {
		vel[PrisonNumAngry].x = moveSpeed;
		PrisonAnim[PrisonNumAngry].y = Right;
		lastPrisonerPosition[PrisonNumAngry] = Right;
	}
	if (prisoners[PrisonNumAngry].getPosition().y >= player.getPosition().y) {
		vel[PrisonNumAngry].y = -moveSpeed;
		PrisonAnim[PrisonNumAngry].y = Up;
		lastPrisonerPosition[PrisonNumAngry] = Up;
	}
	if (prisoners[PrisonNumAngry].getPosition().y <= player.getPosition().y + 32) {
		vel[PrisonNumAngry].y = moveSpeed;
		PrisonAnim[PrisonNumAngry].y = Down;
		lastPrisonerPosition[PrisonNumAngry] = Down;
	}
	//std::cout << "Prisoner Position X: " << prisoners[PrisonNumAngry].getPosition().x << " , Y: " << prisoners[PrisonNumAngry].getPosition().y << std::endl;
	//std::cout << "Player Position X: " << player.getPosition().x << " , Y: " << player.getPosition().y << std::endl;
	prisoners[PrisonNumAngry].move(vel[PrisonNumAngry].x, vel[PrisonNumAngry].y); // making the prisoner follow the player 
	lastVelocity[PrisonNumAngry] = sf::Vector2f(-vel[PrisonNumAngry].x, -vel[PrisonNumAngry].y);


	if (player.characterSprite.getGlobalBounds().intersects(prisoners[PrisonNumAngry].getGlobalBounds())) {
		if (hud.playerArmour >= 1) {
			hud.playerArmour -= 1;
		}
		if (hud.playerArmour == 0) {
			hud.healthBar -= 5; // losing health from enemy attacking
		}
		//std::cout << "Prisoner Attacking" << std::endl;
	}

	//If the prisoner is within a 300 pixel range to the player, the prisoner can follow the player, else go back to wandering - add reduction to prisoner rep later
	if (prisoners[PrisonNumAngry].getPosition().x < player.getPosition().x - 192 || prisoners[PrisonNumAngry].getPosition().x > player.getPosition().x + 192 &&
		prisoners[PrisonNumAngry].getPosition().y < player.getPosition().y - 192 || prisoners[PrisonNumAngry].getPosition().y > player.getPosition().y + 192) {
		//	std::cout << "Player out of range" << std::endl;
		hud.playerArmour += 1;
		prisonerAttacked = false;
		PState = IDLE;
	}

}

void Prisoner::prisonerState() {

}


