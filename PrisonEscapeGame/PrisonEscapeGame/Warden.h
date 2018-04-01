#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

enum wardenState { wardenIDLE, wardenSTOP, wardenDESTINATION }; // moving idly, walking to destination, and chasing the player

class Warden
{
public:
	Warden(std::string wardenFile, sf::RenderWindow &window);
	~Warden();

	std::vector<sf::RectangleShape>  Wardens;
	std::vector<sf::Texture>  wardenTexture;
	float wardenX, wardenY; // position X and Y
	void CollisionResponse();
	sf::Vector2f lastVelocity;

	float moveSpeed = 15;
	sf::Vector2f vel;


	sf::Clock WardenClock;
	int WardenTime = 0;
	int WardenMove = 0; // the random number generated to see which state the prisoner is in
	int WardenHealth = 500;


	void drawWarden(sf::RenderWindow &window);
	void WardenState();
	void onCollision();

	bool wardenAttacked = false;

	sf::Vector2f getPosition() {
		for (int i = 0; i < Wardens.size(); i++) {
			return Wardens[i].getPosition();
		}
	}



};

