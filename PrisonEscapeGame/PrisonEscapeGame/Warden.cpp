#include "Warden.h"
#include <iostream>

std::string wardenfilename = "file.txt";
int wardenNumber;
std::stringstream wss;
std::string ws;
std::string wardenPath;

Warden::Warden(std::string wardenFile, sf::RenderWindow &window)
{
	std::ifstream myInputFile;
	myInputFile.open(wardenFile, std::ios_base::in);
	if (myInputFile.is_open())
	{
		//read the first line which has the number of elements
		std::getline(myInputFile, ws);
		wss.str(ws);
		wss.ignore(18);
		wss >> wardenNumber;
		Wardens.resize(wardenNumber);
		wardenTexture.resize(wardenNumber);

		wss.clear();


		float sizeX, sizeY;



		for (int i = 0; i < wardenNumber; i++)
		{

			//NAME AND NUMBER
			//POSITION
			//SIZE

			//TEXTURE
			getline(myInputFile, ws);
			wss.clear();
			wss.str(ws);
			getline(myInputFile, ws);
			wss.clear();
			wss.str(ws);
			wss >> wardenX >> wardenY;
			getline(myInputFile, ws);
			wss.clear();
			wss.str(ws);
			wss >> sizeX >> sizeY;
			getline(myInputFile, ws);
			wss.clear();
			wss.str(ws);
			wss >> wardenPath;

			sf::Vector2i pos(wardenX, wardenY);
			sf::Vector2f size(sizeX, sizeY);


			if (!wardenTexture[i].loadFromFile(wardenPath)) {
				std::cout << "Load fail Error on guardTexture" << std::endl;
				system("pause");
			}


			Wardens[i].setPosition(pos.x, pos.y);
			Wardens[i].setOrigin(size / 2.0f);
			Wardens[i].setSize(size);
			Wardens[i].setTexture(&wardenTexture[i]);


		}
	}
}


Warden::~Warden()
{
}



enum WardenDir { Down, Right, Up, Left, Idle };
WardenDir lastWardenPosition = Down;
sf::Vector2i WardenAnim(1, Down);

void Warden::CollisionResponse()
{

	for (int i = 0; i < Wardens.size(); i++) {
		std::cout << "Prisoner Collision: " << i << std::endl;
		Wardens[i].move(lastVelocity);
	}
}


void Warden::drawWarden(sf::RenderWindow &window) {

	wardenState::wardenIDLE; // setting the player defaultly to IDLE
	vel.x = 0;
	vel.y = 0;

	std::string SecondsString = std::to_string(WardenTime);
	sf::Time TimeElapsed = WardenClock.getElapsedTime(); // setting the time to the hud clock, so it can count seconds
	sf::Time seconds = sf::seconds(1); // this is to compare to the time elapsed to get 1 second


	if (TimeElapsed >= seconds) { // if the time elapsed is a second, increment the HUDTime and restart the HUDClock 
		WardenTime++;
		WardenClock.restart();

		std::cout << WardenTime << std::endl;
	}
	/*
	if (wardenState::wardenIDLE) {
		if (WardenTime >= 2) {
			WardenMove = rand() % 6; // a random number generator between 1 and 8
			WardenTime = 0;
		}

		if (WardenMove == 1) {
			if (WardenSprite.getPosition().y < 4352) {
				vel.y -= moveSpeed;
				WardenAnim.y = Up;
				lastWardenPosition = Up;
			}
		}
		else if (WardenMove == 2) {
			if (WardenSprite.getPosition().x > 64) {
				vel.x -= moveSpeed;
				WardenAnim.y = Left;
				lastWardenPosition = Left;
			}
		}
		else if (WardenMove == 3) {
			if (WardenSprite.getPosition().y > 64) {
				vel.y += moveSpeed;
				WardenAnim.y = Down;
				lastWardenPosition = Down;
			}
		}
		else if (WardenMove == 4) { // Right Facing warden
			if (WardenSprite.getPosition().x < 2752) {
				vel.x += moveSpeed;
				WardenAnim.y = Right;
				lastWardenPosition = Right;
			}
		}
		else {
			WardenAnim.y = Idle;
			lastWardenPosition = Idle;
		}
	}*/
	for (int i = 0; i < Wardens.size(); i++) {
		Wardens[i].move(vel.x, vel.y);
		WardenAnim.x++;
		for (int i = 0; i < wardenTexture.size(); i++) {
			if (WardenAnim.x * 32 >= wardenTexture[i].getSize().x) { // once the sprite reaches the end of the sprite sheet, reset to 0 again
				WardenAnim.x = 0;
			}
		}

		Wardens[i].setTextureRect(sf::IntRect(WardenAnim.x * 32, WardenAnim.y * 32, 32, 32)); // cropping the image with the position and size of the image 



		window.draw(Wardens[i]);

	}



}


void Warden::WardenState() {

}
void Warden::onCollision()
{

}