#include "Player.h"



Player::Player(sf::Vector2f size, sf::Vector2f position, HUD &hud) {
	playerDamage = 1 + (hud.playerStrength / 3); // making the player damage a third of the hud player strength (?/100) + the initial player damage (1)
	if (!spriteTexture.loadFromFile("../assets/image_assets/characters/sprite_images.png"))
		std::cerr << "Error";
	characterSprite.setSize(size);
	characterSprite.setOrigin(size / 2.0f);
	characterSprite.setTexture(&spriteTexture);
	characterSprite.setPosition(position);

}

enum CharMove { Down, Right, Up, Left, AttackRight, AttackLeft, AttackUp, AttackDown };
CharMove lastPosition = Down;
sf::Vector2i CharAnim(1, Down); // this is a vector with 2 values, the x being the number multiplied by the image width, and the second is the direction


void Player::playerKeyboardMovement(sf::View &view, sf::RenderWindow &window, HUD &hud) {

	vel.x = 0;
	vel.y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		vel.y -= (moveSpeed + (hud.playerStamina / 4));
		CharAnim.y = Up;
		lastPosition = Up;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		vel.y += (moveSpeed + (hud.playerStamina / 4));
		CharAnim.y = Down;
		lastPosition = Down;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		vel.x -= (moveSpeed + (hud.playerStamina / 4));
		CharAnim.y = Left;
		lastPosition = Left;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		vel.x += (moveSpeed + (hud.playerStamina / 4));
		CharAnim.y = Right;
		lastPosition = Right;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (lastPosition == Right) {
			CharAnim.y = AttackRight;
			lastPosition = AttackRight;
		}
		if (lastPosition == Left) {
			CharAnim.y = AttackLeft;
			lastPosition = AttackLeft;
		}
		if (lastPosition == Up) {
			CharAnim.y = AttackUp;
			lastPosition = AttackUp;
		}
		if (lastPosition == Down) {
			CharAnim.y = AttackDown;
			lastPosition = AttackDown;
		}

	}


	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
	{
		CharAnim = sf::Vector2i(1, lastPosition);
	}

	characterSprite.move(vel.x, vel.y);
	lastVelocity = sf::Vector2f(-vel.x, -vel.y);

	clock.restart();
	CharAnim.x += 1; // incrementing the character direction x, to flick through sprite images	
	if (CharAnim.x * 32 >= spriteTexture.getSize().x)
	{// if the texture width is greater than 
		CharAnim.x = 0; // when it reaches the edge, go back to 0
	}
	characterSprite.setTextureRect(sf::IntRect(CharAnim.x * 32, CharAnim.y * 32, 32, 32)); // drawing the rectangles position, width and height
	window.draw(characterSprite);

}

void Player::CollisionResponse()
{
	characterSprite.move(lastVelocity);
}

