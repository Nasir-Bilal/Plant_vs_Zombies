#pragma once
#pragma once
#include "iostream"
#include "Plant.h"
#include "../coordinates.h"
#include "../Elements/SunFactory.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

class SunFlower : public Plant {
public:
    sf::Clock makeSunClock;
    SunFactory& sunFactory;
public:
    SunFlower(int c, int r, SunFactory& sf, int id) :Plant(c, r, id), sunFactory(sf)
    {
        if (!plantImage.loadFromFile("../SFML/Images/Spritesheets/sunflower.png")) {
            // Error handling: unable to load image
            std::cerr << "Failed to load frame sheet image!" << std::endl;
            // You may add additional error handling or throw an exception here
        }
        plantTexture.loadFromImage(plantImage);
        plantSprite.setTexture(plantTexture);
        plantSprite.setTextureRect(plantSourceRect);
        plantSprite.setPosition(coord.x, coord.y);
       // plantSprite.setOrigin(0, 0);

        currentFrame = 0;
        numFrames = 18;
        frameDuration = 80.0f; // adjust as needed
        frameClock.restart();
        costPlant = 50;
    }
    virtual void displayAndUpdateAnimation() override {
        //std::cout << "Elapsed time: " << frameClock.getElapsedTime().asMicroseconds() << " seconds" << std::endl;
        //std::cout << "Frame duration: " << frameDuration << " seconds" << std::endl;

        if (frameClock.getElapsedTime().asMilliseconds() >= frameDuration) //(frameClock.getElapsedTime().asMicroseconds() >= frameDuration) {
        {
            currentFrame = (currentFrame + 1) % numFrames;
            plantSourceRect.left = currentFrame * 91;
            plantSprite.setTextureRect(plantSourceRect);
            frameClock.restart();
        }
    }

    void generateSuns()
    {
        if (makeSunClock.getElapsedTime().asSeconds() >= 10.0)
        {
            // Calculate position relative to sunflower's position
            coordinats sunPosition;
            sunPosition.x = coord.x + 50; // Example: 50 pixels right of sunflower
            sunPosition.y = coord.y - 20; // Example: 20 pixels above sunflower

            // Create sun at calculated position
            sunFactory.createSun(sunPosition);

            makeSunClock.restart(); // Reset the create clock
        }
    }
};