
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
		Clock headClock;
		int headCounter;
		bool headFall;

		Sprite deadSprite;
		Texture deadTexture;
		Clock deadClock;
		int deadCounter;
		

		string headFallstr = "../SFML/Images/zombies/simple/headFall.png";
		string noHeadWalk = "../SFML/Images/zombies/simple/noHeadWalk.png";
		string noHeadEat ="../SFML/Images/zombies/simple/noHeadEat.png";
		string eat = "../SFML/Images/zombies/simple/Eat.png";
		string walk= "../SFML/Images/zombies/simple/walk.png";
		string dead= "../SFML/Images/zombies/simple/die.png";


	public:
		simpleZ(int x, int y) : Zombie(x, y, 10, 1, 10) , animationCounter(0)
		{

			head = true;
			life = 12;
			isEating = false;
			textureIndex = 0;
			headFall = false;
			headCounter = 0;
			isDead = false;

			

			texturePath = walk;
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

			// Loading dead sprite
			if (!deadTexture.loadFromFile(dead))
			{
				cout << "Error loading dead sprite texture" << endl;
			}
			deadSprite.setTexture(deadTexture);
			deadSprite.setTextureRect(sf::IntRect(0, 0, 150, 186)); // Adjust the rectangle size according to your sprite's dimensions

			
			int deadCounter = 0; // Initialize to 0

		}

		void changeTexture(int number)
		{
			textureIndex = number;
		

				if (textureIndex == 0) //walk
				{
					tempTexturePath = texturePath;
					texturePath = life > 6 ? walk : noHeadWalk;

					if (texturePath == walk)
						textureIndex = 0;
					else
						textureIndex = 2;
					

				} 
				else if (textureIndex == 1) //eat and no head eat
				{
					tempTexturePath = texturePath;
					texturePath = life >= 6 ? eat : (isDead?dead:noHeadEat);


				

					if (texturePath == noHeadEat)
						textureIndex = 3;
					else if (texturePath == eat)
						textureIndex = 1;
					else
						textureIndex = 4;

					//just to avoid the rippling of textures otherwise both textures
					//start loading 
				}
				else if (textureIndex == 2) //no head walk
				{
					tempTexturePath = texturePath;
					texturePath = noHeadWalk;

				}
				else if (textureIndex == 3) //no head eat
				{
					tempTexturePath = texturePath;
					texturePath = noHeadEat;

				}
				else if (textureIndex == 4)
				{
					tempTexturePath = texturePath;
					texturePath = dead;
				}


				if(tempTexturePath != texturePath) //to prevent loading textures if already loaded
				{
					if (!texture.loadFromFile(texturePath))
					{
						cout << "Error zombie "<<texturePath << endl;
					}
					sprite.setTexture(texture);
					sprite.setTextureRect(sf::IntRect(0, 0, 166, 144));
					animationCounter = 0;
					
				
					cout << endl << endl << "##############################" << texturePath
						<< "##############################" << endl << endl;

					if(textureIndex==2 ) //if the sprite of noHead is loaded then set head to false
					{
						head = false;
					}

					//if any head fall sprite is loaded then headfall turns true;
					if (!headFall )//&& (texturePath == noHeadEat || texturePath == noHeadWalk))
					{
						if(tempTexturePath == walk && texturePath == noHeadWalk)
						{
							headFall = true;

							headSprite.setPosition(positionZ.x + 49, positionZ.y + 11);
						}
						else if (tempTexturePath==eat && texturePath == noHeadEat)
						{
							headFall = true;

							headSprite.setPosition(positionZ.x + 49, positionZ.y + 11);
						}

						//49 and 11 are the calculated values to adjust the position of head
						// 
						tempTexturePath = texturePath;

					}				
				}
		}

	



		//general logic to change the frame
		void changeFrame(int timeLimit, int totalFrames, int width, int height,
			int& animationCounter ,Sprite& sprite , Clock& animationClock)
		{
			if (animationClock.getElapsedTime().asMilliseconds() > timeLimit)
			{
				animationCounter++;
				if (animationCounter >= totalFrames-1)
				{
					if (timeLimit == 180) //only deals the falling head
					{
						headFall = false;
						animationCounter=0;
			
					}
					else if (timeLimit == 170)
					{
						life = -1;
						animationCounter = 0;
						
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
				changeFrame(200, 22, 166, 144,animationCounter,sprite, animationClock);
			else if (textureIndex == 1) //attack
				changeFrame(200, 21, 166, 144, animationCounter, sprite, animationClock);
			else if (textureIndex == 2) //no head
				changeFrame(200, 18, 166, 144, animationCounter, sprite, animationClock);
			else if (textureIndex == 3) //no head
				changeFrame(200, 11, 166, 144, animationCounter, sprite, animationClock);
			else if ( textureIndex == 4)
				changeFrame(170, 10, 166, 144, animationCounter, sprite, animationClock);


			//running animation for headFall

			if (headFall)
			{
				changeFrame(180, 12, 150, 186, headCounter,headSprite, headClock);
				headSprite.setScale(0.9f, 0.9f);
				window.draw(headSprite);
				cout << "headbeing drawn";
			}
			
			
		}

		//being called in delete zombie class
		void refreshAnimation()
		{



			//if life is less then 6 then change texture to no head eat

			if (isDead)
			{
				changeTexture(4); //dead
			}

			else if (life <= 6 && isEating)
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