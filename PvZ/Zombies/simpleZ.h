

	#pragma once
	#include <SFML/Graphics.hpp>
	#include <iostream>

	using namespace sf;
	using namespace std;

	class simpleZ : public Zombie
	{

		int animationCounter;
	

		Sprite headSprite;
		Texture headTexture;
		int headCounter;
		bool headFall;

		string headFallstr = "../SFML/Images/zombies/simple/headFall.png";
		string noHeadWalk = "../SFML/Images/zombies/simple/noHeadWalk.png";
		string noHeadEat ="../SFML/Images/zombies/simple/noHeadEat.png";


	public:
		simpleZ(int x, int y) : Zombie(x, y, 10, 1, 10) , animationCounter(0)
		{

			head = true;
			life = 10;
			isEating = false;
			textureIndex = 0;
			headFall = false;
			headCounter = 0;

			texturePath = "../SFML/Images/zombies/simple/walk.png";
			//setting the initial texture to walking zombie
			if (!texture.loadFromFile(texturePath))
			{
				cout << "Error zombie" << endl;
			}
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 0, 166, 144));


			//loading head sprite
			if (!headTexture.loadFromFile(headFallstr))
			{
				cout << "Error zombie" << endl;
			}
			headSprite.setTexture(headTexture);
			headSprite.setTextureRect(sf::IntRect(0, 0, 150, 186));



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
					texturePath = life>=6 ? noHeadEat : noHeadWalk;

				

					if (texturePath == noHeadEat)
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
					{
						head = false;
					}

					//if any head fall sprite is loaded then headfall turns true;
					if (!headFall && (texturePath == noHeadEat || texturePath == noHeadWalk))
					{
						headFall = true;
						headSprite.setPosition(positionZ.x, positionZ.y);
					}

					
				}

		
	
		}

	



		//general logic to change the frame
		void changeFrame(int timeLimit, int totalFrames, int width, int height,
			int& animationCounter ,Sprite& sprite)
		{
			if (animationClock.getElapsedTime().asMilliseconds() > timeLimit)
			{
				animationCounter++;
				if (animationCounter >= totalFrames-1)
				{
					if (timeLimit == 180)
					{
						headFall = false;
						animationCounter=0;
			
					}
					else
						animationCounter = 0;
					

				}
				sprite.setTextureRect(sf::IntRect(width * animationCounter, 0, width, height));
				animationClock.restart();
			}
		}

		void animation(RenderWindow& window)
		{
			if (textureIndex == 0) //walk
				changeFrame(200, 22, 166, 144,animationCounter,sprite);
			else if (textureIndex == 1) //attack
				changeFrame(200, 21, 166, 144, animationCounter, sprite);
			else if (textureIndex == 2) //no head
				changeFrame(200, 18, 166, 144, animationCounter, sprite);
			else if (textureIndex == 3) //no head
				changeFrame(200, 11, 166, 144, animationCounter, sprite);


			//running animation for headFall

			if (headFall)
			{
				changeFrame(180, 12, 150, 186, headCounter,headSprite);
				
				headSprite.setScale(0.9f, 0.9f);
				window.draw(headSprite);
				cout << "headbeing drawn";
			}
			
		}

		//being called in delete zombie class
		void refreshAnimation()
		{
			//if life is less then 6 then change texture to no head eat
			if (life <= 6 && isEating)
			{
				changeTexture(3);  // no head attack
			}
			else if (life <= 6 && head)
			{
				changeTexture(2);	 //no head

			}
			else if(isEating)
			{
				changeTexture(1); //attack
			}
			
			


		}
	
	};