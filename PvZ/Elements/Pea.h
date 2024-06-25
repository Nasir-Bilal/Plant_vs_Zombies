#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../coordinates.h"
using namespace std;
using namespace sf;
class Pea {
public:
  //  float x, y;
    coordinats peaPosition;
    bool exists;
    sf::Clock peaClock;
    sf::Sprite sprite;
    sf::Texture texture; // Add a texture member

    Pea() : peaPosition(0,0), exists(false) {
        if (!texture.loadFromFile("pea.png")) {
            // Handle error (texture loading failed)
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 28, 28));
    }

    void shoot(float plantX, float plantY) {
        if ( !exists) {
            //setting the initial position of Pea
            peaPosition.y = plantY+10;
            peaPosition.x = plantX+60;
            exists = true;
        }
    }

    void move() {

        if (exists && peaClock.getElapsedTime().asMilliseconds() < .0115f )
        {
            return;
        }

       peaClock.restart();
       peaPosition.x += 5;

        if (peaPosition.x > 1198)
            exists = false;
    }

    void draw(sf::RenderWindow& window) {
        if (exists) {
            sprite.setPosition(peaPosition.x, peaPosition.y);
            window.draw(sprite);
        }
    }
};

