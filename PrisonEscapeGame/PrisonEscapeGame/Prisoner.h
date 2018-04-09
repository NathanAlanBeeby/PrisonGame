#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Player.h"
#include "HUD.h"
enum prisonerState { IDLE, PathFollow, prisonerAngry }; // moving idly, walking to destination, and chasing the player


class Prisoner
{
public:
	std::vector<sf::RectangleShape>  prisoners;
	std::vector<sf::Texture>  prisonerTexture;
	
	float prisonerX, prisonerY; // position X and Y

	Prisoner(std::string prisonerFile, sf::RenderWindow &window);
	~Prisoner();
	

	sf::Vector2i wayPoint;
	prisonerState PState;

	float moveSpeed = 5.5;
	std::vector<sf::Vector2f> vel;
	std::vector<sf::Vector2f> lastVelocity;


	sf::Vector2f getPosition() {
		for (int i = 0; i < prisoners.size(); i++) {
			return prisoners[i].getPosition();
		}
	}

	int prisonRand;
	int PrisonNumAngry;
	void CollisionResponse(int prisonerNum);


	//void Collision(sf::Vector2f prisonerPosition, sf::Vector2f Size);
	//float Speed = 15;
	sf::Clock PrisonClock;
	int prisonTime = 0;
	int PrisonMove = 0; 
	int prisonerHealth = 100;
	int prisonChoice = 0; // the prisoner thats going to be moved
	
	bool prisonerAttacked = false;

	void drawPrisoner(sf::RenderWindow &window, HUD &hud, Player &player);
	void prisonerState();
	void Wandering(HUD &hud);
	void pathFollowing(HUD &hud);
	void prisonerAttack(HUD &hud, Player &player);

	void PrisonerAttackedChoice(int &prisoner);

	
};

