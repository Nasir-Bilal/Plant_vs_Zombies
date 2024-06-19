
#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "Plants/PlantFactory.h"
#include "Plants/PeaShooter.h"
#include "Elements/Suns.h"
#include "Elements/SunFactory.h"
#include "Elements/Shop.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "coordinates.h"
#include <iostream>
#include <ctime>
#include "../Plants/Plant.h"
#include "../Zombies/zombieFactory.h"
using namespace sf;
using namespace std;

class Levels {
public:
	sf::Image map_image;
	sf::Texture t_map;
	sf::Sprite s_map;

	sf::Image mapp_image;
	sf::Texture tt_map;
	sf::Sprite ss_map;


	bool shopClicked;
	bool gridClicked;
	bool isMousePressed = false;
	coordinats mouse, mouseClick, boxClicked;
	sf::Clock sunClock;
	PlantFactory pFactory;
	SunFactory sFactory;
	Shop myShop;
	pGrid pzGrid;
	zombieFactory zFactory;
	sf::RectangleShape dummyRect;
	int xPos;
	int yPos;
	int xcell;
	int ycell;

	int xgridZ = 0;
	int ygridZ = 0;

	int life;

public:
	Levels() : sunClock(), sFactory(), pFactory(sFactory), myShop(), pzGrid()
	{
		map_image.loadFromFile("../SFML/Images/backwindow.png");
		t_map.loadFromImage(map_image);
		s_map.setTexture(t_map);
		s_map.setPosition(0, 0);
		s_map.setScale(1, 1);
		life = 3;
		mapp_image.loadFromFile("../SFML/Images/grid.png");
		tt_map.loadFromImage(mapp_image);
		ss_map.setTexture(tt_map);
		ss_map.setPosition(280, 130);


		dummyRect.setSize(Vector2f(92, 130));
		//setting dummyrect's with less transparency
		dummyRect.setFillColor(Color(255, 255, 255, 100));
		dummyRect.setPosition(280, 110);
	}
	virtual void createPlants(coordinats mouseClick, int gridX/*mouseX*/, int gridY/*mouseY*/)
	{
		if (!pzGrid.IsEmpty(gridX, gridY))
		{
			cout << "Not empty" << endl;
			return;
		}

		int plantId = myShop.clickPlants(mouseClick) + 1;
		cout << "Plant Id: " << plantId << endl;
		pzGrid.addPlant(gridX, gridY, plantId);
		pFactory.createPlant(gridX, gridY, plantId);
		//pFactory.accessUniqueBehaviors(sFactory);
	}


	void createZombie(Clock& zGeneratClock)
	{
		static int j = 0;

		if (j < 15)
		{
			if (zGeneratClock.getElapsedTime().asSeconds() < 7)
				return;
			zGeneratClock.restart();
			zFactory.generateZombie();
			j++;
		}
	}
	virtual void renderDisplay(sf::RenderWindow& window)
	{
		//displaying backround
		window.draw(s_map);

		//window.draw(ss_map);
		//shop
		myShop.renderShop(window);
		//plants
		pFactory.renderPlants(window);
		//suns
		sFactory.renderSuns(window);
		//zombies
		zFactory.spawnZombie(window);
		movementCollsion();
		
		pFactory.accessUniqueBehaviors(sFactory, window,zFactory);

	}
	void movementCollsion()
	{
		//collision of pea and zombies
	//	pFactory.peaHelpFun1(zFactory);
		zFactory.deleteZombie();

		if (zFactory.clockSimpleZforMove.getElapsedTime().asMilliseconds() < 50)
			return;

		//   gameGrid.display();
		zFactory.clockSimpleZforMove.restart();
		//zombie movement and collision

		if (zFactory.zArray != nullptr)
			for (int i = 0; i < zFactory.zCount; i++)
			{
				zFactory.updatePosition(zFactory.zArray[i]->positionZ, zFactory.zArray[i]->speed);
				xPos = zFactory.zArray[i]->positionZ.x;
				yPos = zFactory.zArray[i]->positionZ.y;


				xcell = ((xPos - 188) / 92) - 1;
				ycell = ((yPos - 130) / 109);
				if (pzGrid.oGrid[(yPos - 130) / 109][(xPos - 188) / 92 - 1].plantId == 1 || pzGrid.oGrid[(yPos - 130) / 109][(xPos - 188) / 92 - 1].plantId == 2)
				{
					cout << "xcell" << xcell << endl;
					cout << "ycell" << ycell << endl;
					//cout << "Zombie reached the plant" << endl;


					//different speed for different zombies
					if (zFactory.zArray[i]->speed == 1)
						zFactory.zArray[i]->positionZ.x += 2;

					if (zFactory.zArray[i]->speed == 2)
						zFactory.zArray[i]->positionZ.x += 3;


					zFactory.zArray[i]->texture.loadFromFile("../SFML/Images/zombieAttack.png");
					zFactory.zArray[i]->sprite.setTexture(zFactory.zArray[i]->texture);
					//health
					if (pFactory.plants[ycell][xcell]->currentHealth > 0)
						pFactory.plants[ycell][xcell]->currentHealth -= 1;
					cout << "current Health: " << pFactory.plants[ycell][xcell]->currentHealth << endl;
					if (pFactory.plants[ycell][xcell]->currentHealth == 0)
					{

						cout << "///////////////////" << endl;
						delete pFactory.plants[ycell][xcell];
						pFactory.plants[ycell][xcell] = nullptr;
						pzGrid.oGrid[ycell][xcell].plantId = 0;
						zFactory.zArray[i]->texture.loadFromFile("../SFML/Images/za.png");
					}


				}


			}
	}
	void shooting()
	{

	}
	virtual void displayPGrid()//sf::RenderWindow& window)
	{
		cout << "Calling display function: " << endl;
		//gameGrid.display();
		pzGrid.displayPlant();
		cout << "Display function exited. " << endl;
	}
	virtual void update(sf::Event& event) = 0;
	SunFactory getSunFactory() const
	{
		return sFactory;
	}
	//virtual void makePanels() = 0;
	virtual void updateGrid(sf::Event& event, sf::RenderWindow& window) = 0;
};

#endif // LEVEL_H