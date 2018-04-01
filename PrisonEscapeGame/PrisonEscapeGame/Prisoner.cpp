#include "Prisoner.h"
#include <iostream>
#include "ParticleEmitter.h"
#include "Player.h"

ParticleSystem particles(500);

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



void Prisoner::CollisionResponse()
{
	
	for (int i = 0; i < prisoners.size(); i++) {
		//std::cout << "Prisoner Collision: " << i << std::endl;
		prisoners[i].move(lastVelocity);
	}
}



void Prisoner::drawPrisoner(sf::RenderWindow &window, HUD &hud, Player &player) {
	PrisonAnim.resize(prisoners.size());
	lastPrisonerPosition.resize(prisoners.size());

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

	//if (PState == IDLE) { // if the prisoner state is idle, the prisoners will wander by calling the wandering function
	//	Wandering(hud);
	//	std::cout << "Prisoner State == Wandering" << std::endl;
	//}
	//else if (PState == prisonerAngry) { // if the prisoner state is set to angry, the function will be called to make the prisoner attack
	//	prisonerAttack(player);
	//	std::cout << "Prisoner State == Attacking" << std::endl;
	//}
	//else { // if the prisoner is not angry or idle, the prisoner should be checking to follow the path
	//	PState = PathFollow;
	//	std::cout << "Prisoner State == PathFollowing" << std::endl;
	//}

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
		//	particles.update(TimeElapsed); // updating by the elapsed time
		//window.draw(particles);
	}


}


void Prisoner::Wandering(HUD &hud) {
	std::string SecondsString = std::to_string(prisonTime);
	sf::Time TimeElapsed = PrisonClock.getElapsedTime(); // setting the time to the hud clock, so it can count seconds
	sf::Time seconds = sf::seconds(1); // this is to compare to the time elapsed to get 1 second

	if (TimeElapsed >= seconds) { // if the time elapsed is a second, increment the HUDTime and restart the HUDClock 
		prisonTime++;
		PrisonClock.restart();
		//std::cout << "Minutes: " << HUDTimeMinute << ", Seconds: " << HUDTime << std::endl;
		std::cout << "Prisoner Time: "<< prisonTime << std::endl;
	}

	if (prisonTime >= 2) { // if the prisonTime exceeds this, move the prisoner, update the random numbers for direction and prisoner selected
		prisonRand = rand() % 4 + 1; // choosing a direction, either 1, 2, 3 or 4 to move in 
		prisonChoice = rand() % prisoners.size(); // generating a random number, depending on how many prisoners there are, and choosing which prisoner to move
		std::cout << "Random prisoner choice: " << prisonChoice << std::endl;
		prisonTime = 0; //setting prison Time back to 0
	}
	


		if (prisonRand == 1) {
			std::cout << "Prisoner Direction Choice: " << prisonRand << std::endl;
			vel.y -= moveSpeed;
			PrisonAnim[prisonChoice].y = Up;
			lastPrisonerPosition[prisonChoice] = Up;
		}
		if (prisonRand == 2) {
			std::cout << "Prisoner Direction Choice: " << prisonRand << std::endl;
			vel.x -= moveSpeed;
			PrisonAnim[prisonChoice].y = Left;
			lastPrisonerPosition[prisonChoice] = Left;
		}
		if (prisonRand == 3) {
			std::cout << "Prisoner Direction Choice: " << prisonRand << std::endl;
			vel.y += moveSpeed;
			PrisonAnim[prisonChoice].y = Down;
			lastPrisonerPosition[prisonChoice] = Down;
		}
		if (prisonRand == 4) {
			std::cout << "Prisoner Direction Choice: " << prisonRand << std::endl;
			vel.x += moveSpeed;
			PrisonAnim[prisonChoice].y = Right;
			lastPrisonerPosition[prisonChoice] = Right;
		}

		prisoners[prisonChoice].move(vel.x, vel.y);
		lastVelocity = sf::Vector2f(-vel.x, -vel.y);
	

	std::cout << "waypoint: " << wayPoint.x << ", " << wayPoint.y << std::endl;
	if (wayPoint.x != 0 && wayPoint.y != 0) { // if the waypoint updates (not bedTime, follow the path)
		std::cout << "State change to path following" << std::endl;
		PState = PathFollow;
	}

	}




void Prisoner::pathFollowing(HUD &hud) {
	if (wayPoint.x != 0 || wayPoint.y != 0) {
		for (int i = 0; i < prisoners.size(); i++) {
			if (prisoners[i].getPosition().x < wayPoint.x +(i * 32)) { // if the prisoners x position is less than the waypoints x position, move positively in the X direction
				vel.x += moveSpeed;
				PrisonAnim[i].y = Right;
				lastPrisonerPosition[i] = Right;
			}
			else if (prisoners[i].getPosition().x > wayPoint.x) {
				vel.x -= moveSpeed;
				PrisonAnim[i].y = Left;
				lastPrisonerPosition[i] = Left;
			}


			if (prisoners[i].getPosition().y < wayPoint.y) { // if the prisoners Y position is less than the waypoints Y position, move positively in the Y direction
				vel.y -= moveSpeed;
				PrisonAnim[i].y = Up;
				lastPrisonerPosition[i] = Up;
			}
			else if (prisoners[i].getPosition().y > wayPoint.y) {
				vel.y += moveSpeed;
				PrisonAnim[i].y = Down;
				lastPrisonerPosition[i] = Down;
			}
			if (prisoners[i].getPosition().x == wayPoint.x + (i * 32) && prisoners[i].getPosition().y == wayPoint.y) {
				PState = IDLE;
			}

		}
	}

	std::string wayPointStringX = std::to_string(wayPoint.x);
	std::string wayPointStringY = std::to_string(wayPoint.y);
	std::cout << "Waypoint position X: " << wayPointStringX << ", Waypoint position Y: "  << wayPointStringY << std::endl;
	/*
	704 192 - prisoner 1
	1024 192 - prisoner 2
	1344 192 - prisoner 3
	1664 192 - prisoner 4
	*/


}

void Prisoner::prisonerAttack(Player &player) {
	
	std::cout << "Players X: " << player.characterSprite.getPosition().x << ", Player Y: " << player.characterSprite.getPosition().y << std::endl;
	std::cout << "Prisoner Under Attack" << std::endl;
	for (int i = 0; i < prisoners.size(); i++) {
		if (prisoners[i].getPosition().x < player.characterSprite.getPosition().x) { // if the prisoners x position is less than the players x, move positive in x
			vel.x += moveSpeed;
			PrisonAnim[i].y = Right;
			lastPrisonerPosition[i] = Right;
		}
		else if (prisoners[i].getPosition().x > player.characterSprite.getPosition().x) {// if the prisoners x position is more than the players x, move negative in x
			vel.x -= moveSpeed;
			PrisonAnim[i].y = Left;
			lastPrisonerPosition[i] = Left;
		}

		if (prisoners[i].getPosition().y < player.characterSprite.getPosition().y) {// if the prisoners y position is less than the players y, move positive in y
			vel.y += moveSpeed;
			PrisonAnim[i].y = Down;
			lastPrisonerPosition[i] = Down;
		}
		else if (prisoners[i].getPosition().y > player.characterSprite.getPosition().y) {// if the prisoners y position is more than the players y, move negative in y
			vel.y -= moveSpeed;
			PrisonAnim[i].y = Up;
			lastPrisonerPosition[i] = Up;
		}
	}
	
}

void Prisoner::prisonerState() {

}


