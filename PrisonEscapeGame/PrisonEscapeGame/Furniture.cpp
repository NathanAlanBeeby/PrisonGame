#include "Furniture.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


std::string furniturefilename = "file.txt";
int  furnitureNumber;
std::stringstream fss;
std::string fs;
std::string furniturePath;

Furniture::Furniture(std::string furnitureFile, sf::RenderWindow &window)
{
	std::ifstream myInputFile;
	myInputFile.open(furnitureFile, std::ios_base::in);
	if (myInputFile.is_open())
	{
		//read the first line which has the number of elements
		std::getline(myInputFile, fs);
		fss.str(fs);
		fss.ignore(21);
		fss >> furnitureNumber;

		furniture.resize(furnitureNumber);
		FurnitureTexture.resize(furnitureNumber);


		fss.clear();


		float sizeX, sizeY;


		for (int i = 0; i < furnitureNumber; i++)
		{

			//NAME AND NUMBER
			//POSITION
			//SIZE
			//TEXTURE
			getline(myInputFile, fs);
			fss.clear();
			fss.str(fs);
			getline(myInputFile, fs);
			fss.clear();
			fss.str(fs);
			fss >> furnX >> furnY;
			getline(myInputFile, fs);
			fss.clear();
			fss.str(fs);
			fss >> sizeX >> sizeY;
			getline(myInputFile, fs);
			fss.clear();
			fss.str(fs);
			fss >> furniturePath;
			fss.clear();
			fss.str(fs);



			sf::Vector2i pos(furnX, furnY);

			sf::Vector2f size(sizeX, sizeY);


			if (!FurnitureTexture[i].loadFromFile(furniturePath)) {
				std::cout << "Load fail Error on FurnitureTexture" << std::endl;
				system("pause");
			}

			furniture[i].setPosition(pos.x, pos.y);
			furniture[i].setSize(sf::Vector2f(size.x, size.y));
			furniture[i].setTexture(&FurnitureTexture[i]);
		}
	}

}


Furniture::~Furniture()
{
	
}



void Furniture::drawFurniture(sf::RenderWindow &window) {
	for (int i = 0; i < furnitureNumber; i++) {
		window.draw(furniture[i]);
	}
}

