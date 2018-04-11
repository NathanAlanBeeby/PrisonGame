#include "furnitureInv.h"
#include "InventoryItems.h"



std::string inventoryFile("../assets/text_assets/InventoryItems.txt");

//inv.drawItems(window);
furnitureInv::furnitureInv()
{
}


furnitureInv::~furnitureInv()
{
}


void furnitureInv::Grid2by2(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	InventoryItems inv(inventoryFile, window);


	std::vector<sf::RectangleShape>  TwoByTwo(4, sf::RectangleShape(gridBox));

	TwoByTwo[0].setPosition(view.getCenter().x - 64, view.getCenter().y - 64);
	TwoByTwo[1].setPosition(view.getCenter().x, view.getCenter().y - 64);
	TwoByTwo[2].setPosition(view.getCenter().x - 64, view.getCenter().y);
	TwoByTwo[3].setPosition(view.getCenter().x, view.getCenter().y);


	for (int i = 0; i < TwoByTwo.size(); i++) {
		TwoByTwo[i].setSize(sf::Vector2f(64, 64));
		TwoByTwo[i].setFillColor(sf::Color(155, 155, 155, 150));
		TwoByTwo[i].setOutlineThickness(2);
		TwoByTwo[i].setOutlineColor(sf::Color(0, 0, 0));
		window.draw(TwoByTwo[i]);
	}

	inv.draw2x2Items(view, window, hud);
}

void furnitureInv::Grid5by2(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	InventoryItems inv(inventoryFile, window);


	std::vector<sf::RectangleShape>  FiveByTwo(10, sf::RectangleShape(gridBox));

	for (int i = 0; i < FiveByTwo.size(); i++) {
		FiveByTwo[i].setSize(sf::Vector2f(64, 64));
		FiveByTwo[i].setFillColor(sf::Color(155, 155, 155, 150));
		FiveByTwo[i].setOutlineThickness(2);
		FiveByTwo[i].setOutlineColor(sf::Color(0, 0, 0));
	}

	for (int i = 0; i < 5; i++) {
		FiveByTwo[i].setPosition(view.getCenter().x - 160 + (i * 64), view.getCenter().y - 64);
		window.draw(FiveByTwo[i]);
	}
	for (int j = 0; j < 5; j++) {
		FiveByTwo[j].setPosition(view.getCenter().x - 160 + (j * 64), view.getCenter().y);
		window.draw(FiveByTwo[j]);
	}

	inv.draw5x2Items(view, window, hud);
}

void furnitureInv::Grid4by4(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	InventoryItems inv(inventoryFile, window);


	std::vector<sf::RectangleShape>  FourByFour(16, sf::RectangleShape(gridBox));

	for (int i = 0; i < FourByFour.size(); i++) {
		FourByFour[i].setSize(sf::Vector2f(64, 64));
		FourByFour[i].setFillColor(sf::Color(155, 155, 155, 150));
		FourByFour[i].setOutlineThickness(2);
		FourByFour[i].setOutlineColor(sf::Color(0, 0, 0));
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			FourByFour[i].setPosition(view.getCenter().x - 128 + (i * 64), view.getCenter().y - 128 + (j * 64));
			window.draw(FourByFour[i]);
		}
	}

	inv.draw4x4Items(view, window, hud);

}



// BIN (2x2)
void furnitureInv::drawBin(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	if (!binTexture.loadFromFile("../assets/image_assets/insideBin.png")) {
		std::cout << "Load fail Error on inside bin" << std::endl;
		system("pause");

	}
	bin.setSize(sf::Vector2f(150, 150));
	bin.setTexture(&binTexture);
	bin.setPosition(view.getCenter().x - 75, view.getCenter().y - 75);
	window.draw(bin);
	Grid2by2(view, window, hud);
}
// DESK (2x2) 
void furnitureInv::drawDesk(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	if (!deskTexture.loadFromFile("../assets/image_assets/insideDesk.png")) {
		std::cout << "Load fail Error on inside bin" << std::endl;
		system("pause");

	}
	desk.setSize(sf::Vector2f(150, 150));
	desk.setTexture(&deskTexture);
	desk.setPosition(view.getCenter().x - 75, view.getCenter().y - 75);
	window.draw(desk);
	Grid2by2(view, window, hud);
}
// LOCKER (2x2)
void furnitureInv::drawLocker(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	if (!lockerTexture.loadFromFile("../assets/image_assets/insideLocker.png")) {
		std::cout << "Load fail Error on inside bin" << std::endl;
		system("pause");

	}
	locker.setSize(sf::Vector2f(150, 150));
	locker.setTexture(&lockerTexture);
	locker.setPosition(view.getCenter().x - 75, view.getCenter().y - 75);
	window.draw(locker);
	Grid2by2(view, window, hud);
}
// BIG BIN (4x4)
void furnitureInv::drawBigBin(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	if (!BigBinTexture.loadFromFile("../assets/image_assets/insideBigBin.png")) {
		std::cout << "Load fail Error on inside big bin" << std::endl;
		system("pause");

	}
	BigBin.setSize(sf::Vector2f(275, 275));
	BigBin.setTexture(&BigBinTexture);
	BigBin.setPosition(view.getCenter().x - 138, view.getCenter().y - 138);
	window.draw(BigBin);
	Grid4by4(view, window, hud);
}
//TOOLS CABINET (4x4)
void furnitureInv::drawToolsCabinet(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	if (!toolsCabinetTexture.loadFromFile("../assets/image_assets/insideToolsCabinet.png")) {
		std::cout << "Load fail Error on inside big bin" << std::endl;
		system("pause");

	}
	toolsCabinet.setSize(sf::Vector2f(275, 275));
	toolsCabinet.setTexture(&toolsCabinetTexture);
	toolsCabinet.setPosition(view.getCenter().x - 138, view.getCenter().y - 138);
	window.draw(toolsCabinet);
	Grid4by4(view, window, hud);
}
// FOOTLOCKER (5x2)
void furnitureInv::drawFootLocker(sf::View &view, sf::RenderWindow &window, HUD &hud) {
	if (!footLockerTexture.loadFromFile("../assets/image_assets/insideFootLocker.png")) {
		std::cout << "Load fail Error on inside big bin" << std::endl;
		system("pause");

	}
	footLocker.setSize(sf::Vector2f(350, 150));
	footLocker.setTexture(&footLockerTexture);
	footLocker.setPosition(view.getCenter().x - 175, view.getCenter().y - 75);
	window.draw(footLocker);
	Grid5by2(view, window, hud);
}