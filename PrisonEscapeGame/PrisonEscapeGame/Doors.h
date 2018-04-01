#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Doors
{
public:
	std::vector<sf::RectangleShape>  doors;
	std::vector<sf::Texture>  DoorTexture;
	//sf::Texture DoorTexture;
	float doorX, doorY; // position X and Y


	Doors(std::string doorsFile, sf::RenderWindow &window);
	~Doors();
	void drawDoors(sf::RenderWindow &window);




};

