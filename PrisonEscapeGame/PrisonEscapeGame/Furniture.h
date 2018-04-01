#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Furniture
{
	// 1 x 1 Objects - Sink and toilet, office chair, locker, shower head
	// 1 x 5 Objects - Caffeteria Bench, 
	// 2 x 1 Objects - Office Desk, Cell Block TV, Sofa, Footlocker, prison bed
	// 2 x 2 Objects - Medical Bed
	// 2 x 5 Objects - Serving Table, Cafeteria Table
public:
	
	//New loading method
	std::vector<sf::RectangleShape>  furniture;
	std::vector<sf::Texture> FurnitureTexture;

	float furnX, furnY; // position X and Y
	


	Furniture(std::string furnitureFile, sf::RenderWindow &window);
	~Furniture();

	void drawFurniture(sf::RenderWindow &window);



	
	
};

