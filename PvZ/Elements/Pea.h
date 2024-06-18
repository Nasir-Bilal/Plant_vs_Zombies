#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Pea {
public:
    float x, y;
    bool exists;
    sf::Clock peaClock;
    sf::Sprite sprite;
    sf::Texture texture; // Add a texture member

    Pea() : x(0), y(0), exists(false) {
        if (!texture.loadFromFile("pea.png")) {
            // Handle error (texture loading failed)
            cout << "not loaded!!!" << endl;
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 28, 28));
    }

    void shoot(float plantX, float plantY) {
        if ( !exists) {
            y = plantY+10;
            x = plantX+80;
            exists = true;
        }
    }

    void move() {
        cout << "////////Pea Clock: " << peaClock.getElapsedTime().asSeconds() << endl;

        if (exists && peaClock.getElapsedTime().asMilliseconds() < .0115f )
        {
            return;
        }

       peaClock.restart();
        x += 5;

        if (x > 1198)
            exists = false;
    }

    void draw(sf::RenderWindow& window) {
        if (exists) {
            sprite.setPosition(x, y);
            window.draw(sprite);
        }
    }
};

