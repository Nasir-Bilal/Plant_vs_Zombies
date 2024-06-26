
#pragma once
#include <SFML/Graphics.hpp>
#include "../Grid.h"
#include "zombies.h"
#include "simpleZ.h"
#include "bucketZ.h"
class zombieFactory
{
public:
    Zombie** zArray;
    int zCount;
    Clock clockSimpleZforMove;


    zombieFactory()
    {
        zArray = new Zombie * [20];
        zCount = 0;
    }
    virtual void generateZombie()
    {

        // zoo[zCount] = new simpleZ;
        srand(time(0));
        int pRow = rand() % 5;
        int randomZombie = rand() % 2; // Assumes you have only two types of zombies

        if (zCount != 19)
            zCount++;

        // Choose zombie type based on random number
        if (randomZombie == 0) {
            zArray[zCount - 1] = new simpleZ(1110, 7 + pRow * 109);
        }
        else {
            zArray[zCount - 1] = new bucketZ(1110, 11 + pRow * 109);
        }


        zArray[zCount - 1]->positionZ.x = 1200;

        zArray[zCount - 1]->positionZ.y = (130 + pRow * 109);


        //gameGrid.oGrid[0][6].iGrid[0][1] = 1;
        cout << zCount << endl;
    }

    void spawnZombie(RenderWindow& window)
    {
        sf::RectangleShape rectangle(sf::Vector2f(23, 23)); // Rectangle size

        rectangle.setFillColor(sf::Color::Blue); // Set fill color

        for (int i = 0; i < zCount; i++)
        {
            zArray[i]->animation();
           
            
            zArray[i]->sprite.setPosition(zArray[i]->positionZ.x, zArray[i]->positionZ.y-20);
            rectangle.setPosition(zArray[i]->positionZ.x, zArray[i]->positionZ.y); 
            zArray[i]->sprite.setScale(0.9f, 0.9f);
            window.draw(zArray[i]->sprite);
            window.draw(rectangle);
         

        }

    }
    void updatePosition(position& positionZ, int speed)
    {
        if (positionZ.x >= 188 && positionZ.y >= 130)
        {
            if (speed == 1)
                positionZ.x -= 2;
            else if (speed == 2)
                positionZ.x -= 2.5;

        }

    }
    bool movementUpdate(RenderWindow& window, pGrid& pzGrid, Zombie**)
    {
        int xPos;
        int yPos;
        if (clockSimpleZforMove.getElapsedTime().asMilliseconds() < 50)
            return false;

        //   gameGrid.display();
        clockSimpleZforMove.restart();
       
        return true;

    }

    void deleteZombie()
    {

        //this function need some adjustments yet
        if(zArray)
        {

            for (int i = 0; i < zCount; i++)
            {
                if (zArray[i]->life <= 0)
                {
                    delete zArray[i];
                    zCount--;
                    for (int j = i; j < zCount; j++)
                    {
                        zArray[j] = zArray[j + 1];
                    }
                  

                }
            }
        }
    }

};