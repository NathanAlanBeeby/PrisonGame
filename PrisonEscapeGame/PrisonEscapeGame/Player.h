#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "HUD.h"

class Player
{

public:

	sf::Texture spriteTexture;
	sf::RectangleShape characterSprite;



	HUD hud;
	float moveSpeed = 10;
	float playerDamage;

	sf::Clock clock;
	sf::Vector2i ScreenSize;

	sf::Vector2f getPosition() { return characterSprite.getPosition(); }
	sf::Vector2f lastVelocity;
	void CollisionResponse();



	int MisOpenCount = 0; // way of knowing if the player has hit the key twice
	int InvOpenCount = 0; // way of knowing if the player has hit the key twice
	int SkilOpenCount = 0; // way of knowing if the player has hit the key twice

	Player(sf::Vector2f size, sf::Vector2f position, HUD &hud);


	void playerKeyboardMovement(sf::View &view, sf::RenderWindow &window, HUD &hud);


	sf::Vector2f vel;





};

//https://www.youtube.com/watch?v=TJtjH5qKBbs - 21:49 24/11/2017