#include "Guard.h"
#include <iostream>
#include "ParticleEmitter.h"

std::string guardfilename = "file.txt";
int guardNumber;
std::stringstream gss;
std::string gs;
std::string guardPath;



Guard::Guard(std::string guardFile, sf::RenderWindow &window)
{
	std::ifstream myInputFile;
	myInputFile.open(guardFile, std::ios_base::in);
	if (myInputFile.is_open())
	{
		//read the first line which has the number of elements
		std::getline(myInputFile, gs);
		gss.str(gs);
		gss.ignore(18);
		gss >> guardNumber;
		guards.resize(guardNumber);
		guardTexture.resize(guardNumber);

		gss.clear();


		float sizeX, sizeY;



		for (int i = 0; i < guardNumber; i++)
		{

			//NAME AND NUMBER
			//POSITION
			//SIZE

			//TEXTURE
			getline(myInputFile, gs);
			gss.clear();
			gss.str(gs);
			getline(myInputFile, gs);
			gss.clear();
			gss.str(gs);
			gss >> guardX >> guardY;
			getline(myInputFile, gs);
			gss.clear();
			gss.str(gs);
			gss >> sizeX >> sizeY;
			getline(myInputFile, gs);
			gss.clear();
			gss.str(gs);
			gss >> guardPath;

			sf::Vector2i pos(guardX, guardY);
			sf::Vector2f size(sizeX, sizeY);


			if (!guardTexture[i].loadFromFile(guardPath)) {
				std::cout << "Load fail Error on guardTexture" << std::endl;
				system("pause");
			}


			guards[i].setPosition(pos.x, pos.y);
			guards[i].setOrigin(size / 2.0f);
			guards[i].setSize(size);
			guards[i].setTexture(&guardTexture[i]);


		}
	}
}


Guard::~Guard()
{
}


enum GuardDir { Down, Right, Up, Left, Idle };
GuardDir lastGuardPosition = Down;
sf::Vector2i GuardAnim(1, Down);

void Guard::CollisionResponse()
{

	for (int i = 0; i < guards.size(); i++) {
		std::cout << "Prisoner Collision: " << i << std::endl;
		guards[i].move(lastVelocity);
	}
}


void Guard::drawGuard(sf::RenderWindow &window) {

	GState == guardIDLE; // setting the player defaultly to IDLE
	vel.x = 0;
	vel.y = 0;

	std::string SecondsString = std::to_string(guardTime);
	sf::Time TimeElapsed = GuardClock.getElapsedTime(); // setting the time to the hud clock, so it can count seconds
	sf::Time seconds = sf::seconds(1); // this is to compare to the time elapsed to get 1 second
	ParticleSystem particles(500);

	if (TimeElapsed >= seconds) { // if the time elapsed is a second, increment the HUDTime and restart the HUDClock 
		guardTime++;
		GuardClock.restart();
		//std::cout << "Minutes: " << HUDTimeMinute << ", Seconds: " << HUDTime << std::endl;
		std::cout << guardTime << std::endl;
	}
	/*
	if (GState == guardIDLE) {
		if (guardTime >= 2) {
			guardMove = rand() % 6; // a random number generator between 1 and 8
			guardTime = 0;
		}

		if (guardMove == 1) {
			if (guardSprite.getPosition().y < 4352) {
				vel.y -= moveSpeed;
				GuardAnim.y = Up;
				lastGuardPosition = Up;
			}
		}
		else if (guardMove == 2) {
			if (guardSprite.getPosition().x > 64) {
				vel.x -= moveSpeed;
				GuardAnim.y = Left;
				lastGuardPosition = Left;
			}
		}
		else if (guardMove == 3) {
			if (guardSprite.getPosition().y > 64) {
				vel.y += moveSpeed;
				GuardAnim.y = Down;
				lastGuardPosition = Down;
			}
		}
		else if (guardMove == 4) { // Right Facing Prisoner
			if (guardSprite.getPosition().x < 2752) {
				vel.x += moveSpeed;
				GuardAnim.y = Right;
				lastGuardPosition = Right;
			}
		}
		else {
			GuardAnim.y = Idle;
			lastGuardPosition = Idle;
		}
	}
	*/
	for (int i = 0; i < guards.size(); i++) {
		guards[i].move(vel.x, vel.y);
		lastVelocity = sf::Vector2f(-vel.x, -vel.y);

		GuardAnim.x++;
		for (int i = 0; i < guardTexture.size(); i++) {
			if (GuardAnim.x * 32 >= guardTexture[i].getSize().x) { // once the sprite reaches the end of the sprite sheet, reset to 0 again
				GuardAnim.x = 0;
			}
		}

		guards[i].setTextureRect(sf::IntRect(GuardAnim.x * 32, GuardAnim.y * 32, 32, 32)); // cropping the image with the position and size of the image 
	}

		for (int i = 0; i < guards.size(); i++) {
			window.draw(guards[i]);
		}

	
	

}


void Guard::guardState() {

}
