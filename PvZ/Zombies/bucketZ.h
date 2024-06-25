#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class bucketZ : public Zombie
{

	int animationCounter = 0;

public:
	bucketZ(int x, int y) : Zombie(x, y, 10, 2, 10)
	{
		if (!texture.loadFromFile("../SFML/Images/buckethead.png"))
		{
			cout << "Error zombie" << endl;
		}
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 166, 152));

	}

	void animation(RenderWindow& window)
	{
		if (animationClock.getElapsedTime().asMilliseconds() > 230)
		{
			animationCounter++;
			if (animationCounter == 15)
			{
				animationCounter = 0;
			}
			sprite.setTextureRect(sf::IntRect(166 * animationCounter, 0, 130, 144));
			animationClock.restart();
		}

		//sprite.setTextureRect(sf::IntRect(166  , 0, 168, 152));



	}


};