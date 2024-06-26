

	#pragma once
	#include <SFML/Graphics.hpp>
	#include <iostream>

	using namespace sf;
	using namespace std;

	class simpleZ : public Zombie
	{

		int animationCounter;
	

	public:
		simpleZ(int x, int y) : Zombie(x, y, 10, 1, 10) , animationCounter(0)
		{
			textureIndex = 0;
			texturePath = "../SFML/Images/zombies/simple/walk.png";
			//setting the initial texture to walking zombie
			if (!texture.loadFromFile(texturePath))
			{
				cout << "Error zombie" << endl;
			}
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 0, 166, 144));

		}

		void changeTexture(int number)
		{
			textureIndex = number;
		

				if (textureIndex == 0)
				{
					tempTexturePath = texturePath;
					texturePath = "../SFML/Images/zombies/simple/walk.png";

				}
				else if (textureIndex == 1)
				{
					tempTexturePath = texturePath;
					texturePath = "../SFML/Images/zombies/simple/eat.png";
				}

				if(tempTexturePath != texturePath)
				{
					if (!texture.loadFromFile(texturePath))
					{
						cout << "Error zombie "<<texturePath << endl;
					}
					sprite.setTexture(texture);
					sprite.setTextureRect(sf::IntRect(0, 0, 166, 144));
					tempTexturePath = texturePath;
				}

		
	
		}

	



		//general logic to change the frame
		void changeFrame(int timeLimit, int totalFrames, int width, int height)
		{
			if (animationClock.getElapsedTime().asMilliseconds() > timeLimit)
			{
				animationCounter++;
				if (animationCounter == totalFrames-1)
				{
					animationCounter = 0;
				}
				sprite.setTextureRect(sf::IntRect(width * animationCounter, 0, width, height));
				animationClock.restart();
			}
		}

		void animation()
		{
			if (textureIndex == 0) //walk
				changeFrame(200, 22, 166, 144);
			else if (textureIndex == 1) //attack
				changeFrame(200, 21, 166, 144);
		}

	
	};