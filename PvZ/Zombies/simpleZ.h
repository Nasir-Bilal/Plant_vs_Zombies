

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class simpleZ : public Zombie
{

	int animationCounter = 0;

public:
	simpleZ(int x, int y) : Zombie(x, y, 10, 1, 10)
	{
		if (!texture.loadFromFile("../SFML/Images/za.png"))
		{
			cout << "Error zombie" << endl;
		}
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 168, 152));

	}

	void animation()
	{
		if (animationClock.getElapsedTime().asMilliseconds() > 200)
		{
			animationCounter++;
			if (animationCounter == 21)
			{
				animationCounter = 0;
			}
			sprite.setTextureRect(sf::IntRect(166 * animationCounter, 0, 166, 144));
			animationClock.restart();
		}

		//sprite.setTextureRect(sf::IntRect(166  , 0, 168, 152));



	}


};