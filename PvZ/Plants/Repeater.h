#pragma once
#include "iostream"
#include "Plant.h"
#include "../coordinates.h"
#include "../Elements/Pea.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class Repeater :public Plant {
private:

public:
    Repeater(int r, int c, int id) :Plant(c, r, id)
    {
        if (!plantImage.loadFromFile("../SFML/Images/Spritesheets/repeater.png")) {
            // Error handling: unable to load image
            std::cerr << "Failed to load frame sheet image!" << std::endl;
            // You may add additional error handling or throw an exception here
        }
        plantTexture.loadFromImage(plantImage);
        plantSprite.setTexture(plantTexture);
        plantSprite.setTextureRect(plantSourceRect);
        plantSprite.setPosition(coord.y, coord.x);
        plantSprite.setOrigin(0, 0);

        currentFrame = 0;
        numFrames = 15;
        frameDuration = 80.0f; // adjust as needed
        frameClock.restart();
        //shootClock.restart();
        costPlant = 200;
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
    ~Repeater()
    {

    }
};