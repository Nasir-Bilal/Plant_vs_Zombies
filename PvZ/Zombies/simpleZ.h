

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

			head = true;
			life = 10;

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
					texturePath = life>=6 ? "../SFML/Images/zombies/simple/eat.png" :
						"../SFML/Images/zombies/simple/noHeadEat.png";

				

					if (texturePath == "../SFML/Images/zombies/simple/noHeadEat.png")
						textureIndex = 3;
					else
						textureIndex = 1;
					//just to avoid the rippling of textures otherwise both textures
					//start loading 
				}
				else if (textureIndex == 2)
				{
					tempTexturePath = texturePath;
					texturePath = "../SFML/Images/zombies/simple/noHeadWalk.png";

				}
				else if (textureIndex == 3)
				{
					tempTexturePath = texturePath;
					texturePath = "../SFML/Images/zombies/simple/noHeadEat.png";

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

					cout << endl << endl << "##############################" << texturePath
						<< "##############################" << endl << endl;

					if(textureIndex==2 ) //if the sprite of noHead is loaded then set head to false
						head = false;
				}

		
	
		}

	



		//general logic to change the frame
		void changeFrame(int timeLimit, int totalFrames, int width, int height)
		{
			if (animationClock.getElapsedTime().asMilliseconds() > timeLimit)
			{
				animationCounter++;
				if (animationCounter >= totalFrames-1)
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
			else if (textureIndex == 2) //no head
				changeFrame(200, 18, 166, 144);
			else if (textureIndex == 3) //no head
				changeFrame(200, 11, 166, 144);
			
		}

		//being called in delete zombie class
		void refreshAnimation()
		{
			//if life is less then 6 then change texture to no head eat
			if (life <= 6 && isEating)
			{
				changeTexture(3);
			}
			else if (life <= 6 && head)
			{
				changeTexture(2);	
			}
			else if(isEating)
			{
				changeTexture(1);
			}
			
			


		}
	
	};