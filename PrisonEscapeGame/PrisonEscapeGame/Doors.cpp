#include "Doors.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


std::string doorsfilename = "file.txt";
int doorsNumber;
std::stringstream dss;
std::string ds;
std::string doorsPath;

Doors::Doors(std::string doorsFile, sf::RenderWindow &window)
{
	std::ifstream myInputFile;
	myInputFile.open(doorsFile, std::ios_base::in);
	if (myInputFile.is_open())
	{
		//read the first line which has the number of elements
		std::getline(myInputFile, ds);
		dss.str(ds);
		dss.ignore(21);
		dss >> doorsNumber;
		doors.resize(doorsNumber);
		DoorTexture.resize(doorsNumber);

		dss.clear();


		float sizeX, sizeY;
		float rot; // rotation


		for (int i = 0; i < doorsNumber; i++)
		{

			//NAME AND NUMBER
			//POSITION
			//SIZE
			//ROTATION
			//TEXTURE
			getline(myInputFile, ds);
			dss.clear();
			dss.str(ds);
			getline(myInputFile, ds);
			dss.clear();
			dss.str(ds);
			dss >> doorX >> doorY;
			getline(myInputFile, ds);
			dss.clear();
			dss.str(ds);
			dss >> sizeX >> sizeY;
			getline(myInputFile, ds);
			dss.clear();
			dss.str(ds);
			dss >> rot;
			getline(myInputFile, ds);
			dss.clear();
			dss.str(ds);
			dss >> doorsPath;

			sf::Vector2i pos(doorX, doorY);
			sf::Vector2f size(sizeX, sizeY);


			if (!DoorTexture[i].loadFromFile(doorsPath)) {
				std::cout << "Load fail Error on DoorsTexture" << std::endl;
				system("pause");
			}


			doors[i].setPosition(pos.x, pos.y);
			doors[i].setOrigin(size / 2.0f);
			doors[i].setSize(size);
			doors[i].setRotation(rot);
			doors[i].setTexture(&DoorTexture[i]);



		}
	}
}


Doors::~Doors()
{
}

void Doors::drawDoors(sf::RenderWindow &window) {


	for (int i = 0; i < doors.size(); i++) {
		window.draw(doors[i]);
	}
}

