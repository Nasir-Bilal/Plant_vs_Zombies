
#pragma once
#include "iostream"
#include "Plant.h"
#include "PeaShooter.h"
#include "Sunflower.h"
#include "SnowPea.h"
#include "Repeater.h"
#include <SFML/Graphics.hpp>
#include "../Elements/SunFactory.h"
#include <iostream>
#include <ctime>

class PlantFactory {
public:
    Plant* plants[9][5]; // Array to store pointers to plant objects
    int plantCount; // Number of plants currently stored in the array
    const int MAX_PLANTS;
    SunFactory& sunFactory;
    sf::Clock shootClock;
public:
    // Constructor
    PlantFactory(SunFactory& sf) : plantCount(0), plants(), MAX_PLANTS(9 * 5), sunFactory(sf)
    {
        shootClock.restart();
        //plants[0] = &ps;
    }

    // Destructor


    // Create plant and add to array
    bool createPlant(int gridX, int gridY, int id, int& sunCurrency)
    {

        if (!id)
        {
            return 0;
        }

        switch (id)
        {
        case 1:
            if (sunCurrency >= 50)
            {
                plants[gridY][gridX] = new SunFlower(gridX * 92 + 280, gridY * 110 + 130, sunFactory, 1);
                sunCurrency -= 50;
                return 1;
            }
            break;
        case 2:
            if (sunCurrency >= 100)
            {
                plants[gridY][gridX] = new PeaShooter(gridX * 92 + 280, gridY * 110 + 130, 2);
                sunCurrency -= 100;
                return 1;
            }
            break;
        case 3:
            if (sunCurrency >= 175)
            {
                plants[gridY][gridX] = new SnowPea(gridX * 92 + 280, gridY * 110 + 130, 3);
                sunCurrency -= 175;
                return 1;
            }
            break;
        case 4:
            if (sunCurrency >= 200)
            {
                plants[gridY][gridX] = new Repeater(gridX * 92 + 280, gridY * 110 + 130, 4);
                sunCurrency -= 200;
                return 1;
            }
            break;
        default:
            return 0;
        }
    }
    // Display all plants
    void renderPlants(sf::RenderWindow& window)
    {

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (plants[i][j] != nullptr)
                {
                    plants[i][j]->displayAndUpdateAnimation();
                    plants[i][j]->plantSprite.setScale(0.8f, 0.8f);
                    window.draw(plants[i][j]->plantSprite);
                }
            }
        }


    }
    //void accessUniqueBehaviors(SunFactory& sFactory, sf::RenderWindow& window,zombieFactory& zFactory)
    //{
    //    float deltaTime = shootClock.restart().asSeconds();
    //    //converting above code to into 2d arrays
    //    for (int i = 0; i < 9; i++)
    //    {
    //        for (int j = 0; j < 5; j++)
    //        {
    //            if (plants[i][j] != nullptr)
    //            {
    //                PeaShooter* peaShooter = dynamic_cast<PeaShooter*>(plants[i][j]);
    //                if (peaShooter)
    //                {
    //                    // Access unique behavior of PeaShooter
    //                    //Pea pea;
    //                    peaShooter->peaCollison(zFactory);
    //                    peaShooter->shootPea();
    //                    peaShooter->update(deltaTime);
    //                    peaShooter->render(window);
    //                }
    //
    //                // Check if the current plant is a Sunflower
    //                SunFlower* sunflower = dynamic_cast<SunFlower*>(plants[i][j]);
    //                if (sunflower)
    //                {
    //                    // Access unique behavior of Sunflower
    //                    sunflower->generateSuns();
    //                }
    //            }
    //        }
    //    }
    //
    //}
    void accessUniqueBehaviors(SunFactory& sFactory, sf::RenderWindow& window, zombieFactory& zFactory)
    {
        float deltaTime = shootClock.restart().asSeconds();

        // Iterate over each row of the grid
        for (int j = 0; j < 5; j++)
        {
            bool zombieInRow = false;

            // Check if there's any zombie in the current row
            for (int i = 0; i < zFactory.zCount; i++)
            {
                if (zFactory.zArray[i]->getRowIndex() == j)
                {
                    zombieInRow = true;
                    //cout << "zombie in row: " << zFactory.zArray[i]->getRowIndex() << endl;
                    //break;
                }
            }

            // If there are zombies in the row, update and render PeaShooters
            for (int i = 0; i < 9; i++)
            {
                if (plants[i][j] != nullptr)
                {
                    PeaShooter* peaShooterr = dynamic_cast<PeaShooter*>(plants[i][j]);
                    if (peaShooterr)// && zombieInRow)
                    {
                        // Access unique behavior of PeaShooter
                        peaShooterr->peaCollison(zFactory);
                        peaShooterr->shootPea();
                        peaShooterr->update(deltaTime);
                        peaShooterr->render(window);
                        //zombieInRow = false;
                    }

                    // Check if the current plant is a Sunflower
                    SunFlower* sunflower = dynamic_cast<SunFlower*>(plants[i][j]);
                    if (sunflower)
                    {
                        // Access unique behavior of Sunflower
                        sunflower->generateSuns();
                    }
                }
            }
        }
    }
  
};

