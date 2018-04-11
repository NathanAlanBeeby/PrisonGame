#include "prisonWalls.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string filename = "file.txt";
int numWallsToRead;
std::stringstream ss;
std::string s;


prisonWalls::prisonWalls(std::string wallFile, sf::RenderWindow &window)
{
	if (!wallTexture.loadFromFile("../assets/image_assets/wall.png")) {
		std::cout << "Load fail Error on wallTexture" << std::endl;
		system("pause");
	}

	//setting texture and size
	std::ifstream myInputFile;
	myInputFile.open(wallFile, std::ios_base::in);
	if (myInputFile.is_open())
	{
		//read the first line which has the number of elements
		std::getline(myInputFile, s);
		ss.str(s);
		ss.ignore(17);
		ss >> numWallsToRead;

		Walls.resize(numWallsToRead);


		ss.clear();

		for (int i = 0; i < numWallsToRead; i++)
		{
			getline(myInputFile, s);
			getline(myInputFile, s);
			ss.clear();
			ss.str(s);
			ss >> x >> y;

			sf::Vector2f pos(x, y);
			sf::Vector2f size(64, 64);
			Walls[i].setSize(size);
			Walls[i].setTexture(&wallTexture);
			Walls[i].setPosition(pos.x, pos.y);



		}
	}
}

void prisonWalls::drawWalls(sf::RenderWindow &window) {
	for (int i = 0; i < numWallsToRead; i++) {
		window.draw(Walls[i]);
	}
}
