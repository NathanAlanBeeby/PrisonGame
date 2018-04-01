#pragma once

#include <SFML/Graphics.hpp>
#include "HUD.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

enum NurseState { nurseIDLE, underAttack, nurseDESTINATION, Run }; // moving idly, under attack, desination, and running away from the player

class Nurse
{
public:
	Nurse(std::string nurseFile, sf::RenderWindow &window);
	~Nurse();

	HUD hud;


	float moveSpeed = 20;
	sf::Vector2f vel;



	std::vector<sf::RectangleShape>  nurses;
	std::vector<sf::Texture>  nurseTexture;
	float nurseX, nurseY; // position X and Y
	void CollisionResponse();
	sf::Vector2f lastVelocity;


	sf::Vector2f getPosition() { 
		for (int i = 0; i < nurses.size(); i++) {
			return nurses[i].getPosition();
		}
	 }





	float Speed = 7.5;
	sf::Clock nurseClock;
	int nurseTime = 0;
	int NurseMove = 0; // the random number generated to see which state the prisoner is in
	int NurseHealth = 100;
	bool nurseAttacked = false;

	void drawNurse(sf::RenderWindow &window);
	void NurseState();
	void onCollision();

};

