#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "HUD.h"
class furnitureInv
{
public:
	furnitureInv();
	~furnitureInv();

	sf::RectangleShape gridBox;

	void Grid2by2(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void Grid5by2(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void Grid4by4(sf::View &view, sf::RenderWindow &window, HUD &hud);





	sf::RectangleShape bin, desk, locker, BigBin, toolsCabinet, footLocker;
	sf::Texture binTexture, deskTexture, lockerTexture, BigBinTexture, toolsCabinetTexture, footLockerTexture;

	void drawBin(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void drawDesk(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void drawLocker(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void drawBigBin(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void drawToolsCabinet(sf::View &view, sf::RenderWindow &window, HUD &hud);
	void drawFootLocker(sf::View &view, sf::RenderWindow &window, HUD &hud);
};

