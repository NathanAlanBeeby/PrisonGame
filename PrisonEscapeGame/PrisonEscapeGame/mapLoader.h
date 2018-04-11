#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include "Node.h"

#define MAP_WIDTH 100
#define MAP_HEIGHT 100


class mapLoader
{
public:

	sf::Texture MapTilesTexture; // texture for the map
	sf::Sprite MapTiles; // setting a sprite of tiles
	sf::Vector2i map[100][100]; //map size set to a vector with 2 integers
	sf::Vector2i loadCount = sf::Vector2i(0, 0); // load counter set to 0,0

	Node nodes[100][100];

	void populateNodes() {
		for (int i = 0; i < loadCount.x; i++)
		{
			for (int j = 0; j < loadCount.y; j++)
			{
				nodes[i][j].setPosition(map[i][j]);
			}
		}
	};

	/*


	AStar() {
		do the a star algorithm with the Nodes array as your source
	}

	loadMap() {
		open the map file ONCE, and assign texture to node/tile array
	}

	drawMap() {
		for each node, draw it
	}

	*/

	mapLoader() {
		std::ifstream openfile("../assets/text_assets/Map1.txt");// put in constructor
		if (openfile.is_open()) {
			std::string tileLoc; // creating a string called tile loc for the tile location
			openfile >> tileLoc;
			MapTilesTexture.loadFromFile(tileLoc); // loading the map tile textures from file
			MapTiles.setTexture(MapTilesTexture); //setting the texture
			while (!openfile.eof())
			{
				std::string str; // setting the file name
				openfile >> str; // opening the file

				char x = str[0], y = str[2]; //getting the values of the x,y and comma's


				if (!isdigit(x) || !isdigit(y)) // checking if the digit is a number
					map[loadCount.x][loadCount.y] = sf::Vector2i(-1, -1); //if its not, set the value to -1,-1(shouldn't draw a tile)


				else // if not
					map[loadCount.x][loadCount.y] = sf::Vector2i(x - '0', y - '0'); //chars can be changed into ints and can turn to ascii, this solves that

				if (openfile.peek() == '\n') // openfile.peek checks for the next character in the file, if it is a new line, we then want to change what file is loaded
				{
					loadCount.x = 0; // starting at the next line
					loadCount.y++; // incrementing to the next line
				}
				else
					loadCount.x++; // incrementing through the x coordinate
			}
			loadCount.y++;
		}
	}



	void drawMap(sf::RenderWindow &window) {
		for (int i = 0; i < loadCount.x; i++)
		{
			for (int j = 0; j < loadCount.y; j++)
			{
				if (map[i][j].x != -1 && map[i][j].y != -1)
				{
					MapTiles.setPosition(i * 64, j * 64); // setting I and J multiplied of the size of the tiles
					MapTiles.setTextureRect(sf::IntRect(map[i][j].x * 64, map[i][j].y * 64, 64, 64)); // getting the left, top, width and height
					window.draw(MapTiles);
				}
			}
		}
	}
private:

};
//https://www.youtube.com/watch?v=O7lVymlZMy0