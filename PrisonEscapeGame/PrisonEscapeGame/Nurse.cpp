#include "Nurse.h"
#include <iostream>

std::string nursefilename = "file.txt";
int nurseNumber;
std::stringstream nss;
std::string ns;
std::string nursePath;

Nurse::Nurse(std::string nurseFile, sf::RenderWindow &window)
{
	std::ifstream myInputFile;
	myInputFile.open(nurseFile, std::ios_base::in);
	if (myInputFile.is_open())
	{
		//read the first line which has the number of elements
		std::getline(myInputFile, ns);
		nss.str(ns);
		nss.ignore(18);
		nss >> nurseNumber;
		nurses.resize(nurseNumber);
		nurseTexture.resize(nurseNumber);

		nss.clear();


		float sizeX, sizeY;



		for (int i = 0; i < nurseNumber; i++)
		{

			//NAME AND NUMBER
			//POSITION
			//SIZE

			//TEXTURE
			getline(myInputFile, ns);
			nss.clear();
			nss.str(ns);
			getline(myInputFile, ns);
			nss.clear();
			nss.str(ns);
			nss >> nurseX >> nurseY;
			getline(myInputFile, ns);
			nss.clear();
			nss.str(ns);
			nss >> sizeX >> sizeY;
			getline(myInputFile, ns);
			nss.clear();
			nss.str(ns);
			nss >> nursePath;

			sf::Vector2i pos(nurseX, nurseY);
			sf::Vector2f size(sizeX, sizeY);


			if (!nurseTexture[i].loadFromFile(nursePath)) {
				std::cout << "Load fail Error on guardTexture" << std::endl;
				system("pause");
			}


			nurses[i].setPosition(pos.x, pos.y);
			nurses[i].setOrigin(size / 2.0f);
			nurses[i].setSize(size);
			nurses[i].setTexture(&nurseTexture[i]);


		}
	}
}


Nurse::~Nurse()
{
}


enum NurseDir { Down, Right, Up, Left, Idle };
NurseDir lastNursePosition = Down;
sf::Vector2i NurseAnim(1, Down);

void Nurse::CollisionResponse()
{

	for (int i = 0; i < nurses.size(); i++) {
		std::cout << "Prisoner Collision: " << i << std::endl;
		nurses[i].move(lastVelocity);
	}
}


void Nurse::drawNurse(sf::RenderWindow &window) {

	NurseState::nurseIDLE;
	vel.x = 0;
	vel.y = 0;



	std::string SecondsString = std::to_string(nurseTime);
	sf::Time TimeElapsed = nurseClock.getElapsedTime(); // setting the time to the hud clock, so it can count seconds
	sf::Time seconds = sf::seconds(1); // this is to compare to the time elapsed to get 1 second




	if (TimeElapsed >= seconds) { // if the time elapsed is a second, increment the HUDTime and restart the HUDClock 
		nurseTime++;
		nurseClock.restart();
		//std::cout << "Minutes: " << HUDTimeMinute << ", Seconds: " << HUDTime << std::endl;
		std::cout << nurseTime << std::endl;
	}
	/*
	if (NurseState::nurseIDLE) {
		if (nurseTime >= 5) {
			NurseMove = rand() % 6; // a random number generator between 1 and 8
			nurseTime = 0;
		}



		if (NurseMove == 1) {
			if (nurseSprite.getPosition().y > 64) {
				vel.y -= moveSpeed;
				NurseAnim.y = Up;
				lastNursePosition = Up;
			}
		}
		else if (NurseMove == 2) {
			if (nurseSprite.getPosition().x > 64) {
				vel.x -= moveSpeed;
				NurseAnim.y = Left;
				lastNursePosition = Left;
			}
		}
		else if (NurseMove == 3) {
			if (nurseSprite.getPosition().y < 4416) {
				vel.y += moveSpeed;
				NurseAnim.y = Down;
				lastNursePosition = Down;
			}
		}
		else if (NurseMove == 4) {
			if (nurseSprite.getPosition().x < 2752) {
				vel.x += moveSpeed;
				NurseAnim.y = Right;
				lastNursePosition = Right;
			}
		}
		else {
			NurseAnim.y = Idle;
			lastNursePosition = Idle;
		}

	}
	*/

	for (int i = 0; i < nurses.size(); i++) {
		nurses[i].move(vel.x, vel.y);

		NurseAnim.x++;
		for (int i = 0; i < nurseTexture.size(); i++) {
			if (NurseAnim.x * 32 >= nurseTexture[i].getSize().x) { // once the sprite reaches the end of the sprite sheet, reset to 0 again
				NurseAnim.x = 0;
			}
		}
		nurses[i].setTextureRect(sf::IntRect(NurseAnim.x * 32, NurseAnim.y * 32, 32, 32)); // cropping the image with the position and size of the image 


		window.draw(nurses[i]);
	}


}



void Nurse::NurseState() {

}

void Nurse::onCollision()
{

}