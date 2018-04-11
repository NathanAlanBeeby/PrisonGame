#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

enum guardState { guardIDLE, guardStop, guardDESTINATION, guardCHASE }; // moving idly, walking to destination, and chasing the player

class Guard
{
public:
	Guard(std::string guardFile, sf::RenderWindow &window);
	~Guard();

	guardState GState;

	std::vector<sf::RectangleShape>  guards;
	std::vector<sf::Texture>  guardTexture;
	float guardX, guardY; // position X and Y
	void CollisionResponse();
	sf::Vector2f lastVelocity;



	float moveSpeed = 15;
	sf::Vector2f vel;




	bool guardAttacked = false;
	sf::Clock GuardClock;
	int guardTime = 0;
	int guardMove = 0; // the random number generated to see which state the prisoner is in
	int guardHealth = 200;


	void drawGuard(sf::RenderWindow &window);
	void guardState();



	sf::Vector2f getPosition() {
		for (int i = 0; i < guards.size(); i++) {
			return guards[i].getPosition();
		}
	}




};

