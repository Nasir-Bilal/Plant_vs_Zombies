#pragma once
#include "iostream"
#include "../coordinates.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class shopPanel {
protected:
	sf::Image shopPanelImage;
	sf::Sprite shopPanelSprite;
	sf::Texture shopPanelTexture;
	sf::IntRect shopPanelSourceRect;
	static int placeHere; // keeps count of next panel
	float x, y; //position of panel
	float width, height; //size of panel
public:
	shopPanel() : shopPanelSourceRect(0, 0, 55, 73), width(55),height(73)
	{
		placeHere += 55;
		x = placeHere;
		y = 5; 
	}
	void renderShopPanel(sf::RenderWindow& window)
	{
		window.draw(shopPanelSprite);
	}
	bool isClicked(coordinats mouse) 
	{
		//mouse click within panel
		//std::cout << "Panel position: (" << x << ", " << y << "), size: (" << width << ", " << height << ")" << std::endl;
		//std::cout << "Mouse position: (" << mouse.x << ", " << mouse.y << ")" << std::endl;

		
		if (mouse.x >= x && mouse.x <= x + width && mouse.y >= y && mouse.y <= y + height) 
		{
			
		
			return true;
		}
		return false;
	}
};
int shopPanel::placeHere = 14; //69-55