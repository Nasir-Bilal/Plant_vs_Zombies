
#pragma once
#include "iostream"
#include "Plant.h"
#include "../coordinates.h"
#include "../Elements/Pea.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "../Zombies/zombieFactory.h"
using namespace sf;
using namespace std;


class PeaShooter : public Plant {
public:
    Pea pea;
    Clock shooting;
    int x, y;
    Clock healthClock;
    //this clocks helps to avoid disruption in reducing life
public:
    PeaShooter(int r, int c) :Plant(c, r)
    {
        if (!plantImage.loadFromFile("../SFML/Images/Spritesheets/Peashooter.png")) {
            // Error handling: unable to load image
            std::cerr << "Failed to load frame sheet image!" << std::endl;
            // You may add additional error handling or throw an exception here
        }
        plantTexture.loadFromImage(plantImage);
        plantSprite.setTexture(plantTexture);
        plantSprite.setTextureRect(plantSourceRect);
        plantSprite.setPosition(coord.y, coord.x);
        plantSprite.setOrigin(0, 0);
        x = r;
        y = c;

        currentFrame = 0;
        numFrames = 13;
        frameDuration = 80.0f; // adjust as needed
        frameClock.restart();
        //shootClock.restart();
        costPlant = 100;
    }

    virtual void displayAndUpdateAnimation() override {
        //std::cout << "Elapsed time: " << frameClock.getElapsedTime().asMicroseconds() << " seconds" << std::endl;
        //std::cout << "Frame duration: " << frameDuration << " seconds" << std::endl;

        if (frameClock.getElapsedTime().asMilliseconds() >= frameDuration) //(frameClock.getElapsedTime().asMicroseconds() >= frameDuration) {
        {
            currentFrame = (currentFrame + 1) % numFrames;
            plantSourceRect.left = currentFrame * 92;
            plantSprite.setTextureRect(plantSourceRect);
            frameClock.restart();
        }
    }
   
    ~PeaShooter()
    {
       
    }
    void shootPea() {
      
        //x and y coordinates have been interchanged
        if (shooting.getElapsedTime().asSeconds() < 1.5f) return;
        
        shooting.restart();
        pea.shoot(coord.y, coord.x);
    }

    void update(float deltaTime) {
        pea.move();
      
    }

    void render(sf::RenderWindow& window) {
      
        pea.draw(window);
    }

    void peaCollison(zombieFactory& zFactory)
    {
        for (int i =0 ; i < zFactory.zCount; i++)
        {
          

            if (pea.peaPosition.x >= zFactory.zArray[i]->getX()
                && pea.peaPosition.x <= zFactory.zArray[i]->getX()+30
                && pea.peaPosition.y>= zFactory.zArray[i]->getY()
                && pea.peaPosition.y <= zFactory.zArray[i]->getYBottom())
            { 
                if (healthClock.getElapsedTime().asSeconds() < 0.7f)
                    return;
                healthClock.restart();
                pea.exists = false; //deleting pea
                zFactory.zArray[i]->reducehealth();
                
              

            }

        }



    }
     
};