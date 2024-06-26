
#pragma once
#include <iostream>
#include "../Plants/PlantFactory.h"
#include "../Plants/PeaShooter.h"
#include "../Grid.h"
#include "../Elements/PeaShooterPanel.h"
#include <SFML/Graphics.hpp>
#include "../coordinates.h"
#include "Levels.h"
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

class Level1 : public Levels {
private:

public:
	Level1()
	{
		myShop.makePanels(2);
	}
	virtual void update(sf::Event& event) override
	{
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			isMousePressed = true;
			mouseClick.x = event.mouseButton.x;
			mouseClick.y = event.mouseButton.y;
			if ((mouse.x >= 0 && mouse.x <= 522) && (mouse.y >= 0 && mouse.y <= 90))
			{
				mouseClick.x = (mouse.x);
				mouseClick.y = (mouse.y);
				cout << "click (" << mouseClick.x << ',' << mouseClick.y << ')' << endl;
				shopClicked = true;

			}
			//cout << "(" << mouseX << ',' << mouseY << ')' << endl;
		}
		// Mouse button released
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			mouse.x = event.mouseButton.x;// event.mouseButton.x; 
			mouse.y = event.mouseButton.y;//event.mouseButton.y;
			cout << "(" << mouse.x << ',' << mouse.y << ')' << endl;

			if ((mouse.x >= 230 && mouse.x <= 1109) && (mouse.y >= 130 && mouse.y <= 680))
			{
				boxClicked.x = ((mouse.x) - 280.0) / 92.0;
				boxClicked.y = (mouse.y - 130) / 110;

				cout << "BOX  of grid clicked (" << boxClicked.x << ',' << boxClicked.y << ')' << endl;
				gridClicked = true;

			}
		}
	}
	virtual void updateGrid(sf::Event& event, sf::RenderWindow& window)
	{
		//creating plant
		if (gridClicked && shopClicked)
		{
			//cout << "click22 (" << mouseClick.x << ',' << mouseClick.y << ')' << endl;
			createPlants(mouseClick, boxClicked.x, boxClicked.y);
			displayPGrid();
			gridClicked = false;
			shopClicked = false;
		}
		//collecting suns
		else if (gridClicked && !shopClicked)
		{
			sFactory.checkClick(window, mouse);
			gridClicked = false;
		}
		sFactory.update();
		sFactory.dropAllSuns();
		if (pFactory.plantCount)
		{
			update(event);
		}
	}
};