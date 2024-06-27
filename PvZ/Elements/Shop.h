#pragma once
#include "iostream"
#include "../coordinates.h"
#include "ShopPanel.h"
#include "../Elements/PeaShooterPanel.h"
#include "../Elements/SunFlowerPanel.h"
#include "../Elements/SnowPeaPanel.h"
#include "../Elements/RepeaterPanel.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Shop {
public:
	sf::Image shopImage;
	sf::Sprite shopSprite;
	sf::Texture shopTexture;
	sf::IntRect shopSourceRect;
	shopPanel** panels;
	int numPanels;
public:
	Shop(): shopSourceRect(0,0,522,87),numPanels(0)
	{
		//loading image
		if (!shopImage.loadFromFile("../SFML/Images/Shop/shop.png")) {
			// Error handling: unable to load image
			std::cerr << "Failed to load frame sheet image!" << std::endl;
			// You may add additional error handling or throw an exception here
		}
		shopTexture.loadFromImage(shopImage);
		shopSprite.setTexture(shopTexture);
		shopSprite.setTextureRect(shopSourceRect);
		shopSprite.setPosition(0, 0);
	}
	void renderShop(sf::RenderWindow& window)
	{
		window.draw(shopSprite);
		for (int i = 0; i < numPanels; i++)
		{
			panels[i]->renderShopPanel(window);
		}
	}
	sf::Sprite getShopSprite()const
	{
		return shopSprite;
	}
	shopPanel** getPanel()const
	{
		return panels;
	}
	void setPanel(shopPanel* p)
	{
		panels[numPanels] = p;
		numPanels++;
	}
	void makePanels(int n)
	{
		numPanels = n;
		panels = new shopPanel * [n];
		panels[0] = new SunFlowerPanel();
		panels[1] = new PeaShooterPanel();
		panels[2] = new SnowPeaPanel();
		panels[3] = new RepeaterPanel();
	}
	int clickPlants(coordinats mouse)
	{
		
		int id=0;
		for (int i = 0; i < numPanels; i++)
		{
			
			if (panels[i]->isClicked(mouse))
			{
				std::cout << "Clicking Plants" << std::endl;
				id = i;
				return id;
			}
		}
	}
};