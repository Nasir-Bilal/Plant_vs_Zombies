
#pragma once
#include "iostream"
#include "Plant.h"
#include "PeaShooter.h"
#include "Sunflower.h"
#include <SFML/Graphics.hpp>
#include "../Elements/SunFactory.h"
#include <iostream>
#include <ctime>
using namespace std;
using namespace sf;

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
    void createPlant(int gridX, int gridY, int id)
    {

        if (!id)
        {
            return;
        }

        switch (id)
        {
        case 1:
            plants[gridY][gridX] = new SunFlower(gridX * 92 + 280, gridY * 110 + 130, sunFactory);


            break;
        case 2:
            plants[gridY][gridX] = new PeaShooter(gridX * 92 + 280, gridY * 110 + 130);
            break;
        default:
            return;
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
    void accessUniqueBehaviors(SunFactory& sFactory, sf::RenderWindow& window,zombieFactory& zFactory)
    {
        float deltaTime = shootClock.restart().asSeconds();
        //converting above code to into 2d arrays
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (plants[i][j] != nullptr)
                {
                    PeaShooter* peaShooter = dynamic_cast<PeaShooter*>(plants[i][j]);
                    if (peaShooter)
                    {
                        // Access unique behavior of PeaShooter
                        //Pea pea;
                        peaShooter->peaCollison(zFactory);
                        peaShooter->shootPea();
                        peaShooter->update(deltaTime);
                        peaShooter->render(window);
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

