#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class simpleZ : public Zombie
{
    int animationCounter;
    bool head;
    Sprite headSprite;
    Texture headTexture;
    int headAnimationStep;
    Clock animationClock;
    Clock headAnimationClock;
    bool dead;

public:
    simpleZ(int x, int y) : Zombie(x, y, 10, 1, 10), animationCounter(0), head(false), headAnimationStep(0), dead(false)
    {
        textureIndex = 0;
        texturePath = "../SFML/Images/zombies/simple/walk.png";

        // Initial texture setup for walking zombie
        if (!texture.loadFromFile(texturePath))
        {
            cout << "Error loading zombie texture: " << texturePath << endl;
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 166, 144));

        if (!headTexture.loadFromFile("../SFML/Images/zombies/simple/headFall.png"))
        {
            cout << "Error loading head texture" << endl;
        }
        headSprite.setTexture(headTexture);
        headSprite.setTextureRect(sf::IntRect(0, 0, 150, 186));
    }

    void changeTexture(int number)
    {
        string newTexturePath;

        switch (number)
        {
        case 0:
            newTexturePath = "../SFML/Images/zombies/simple/walk.png";
            break;
        case 1:
            newTexturePath = (life <= 6) ? "../SFML/Images/zombies/simple/noHeadEat.png" : "../SFML/Images/zombies/simple/eat.png";
            break;
        case 2:
            newTexturePath = "../SFML/Images/zombies/simple/noWalk.png";
            break;
        case 3:
            newTexturePath = "../SFML/Images/zombies/simple/die.png";
            break;
        default:
            return;
        }

        if (texturePath != newTexturePath)
        {
            texturePath = newTexturePath;
            if (!texture.loadFromFile(texturePath))
            {
                cout << "Error loading zombie texture: " << texturePath << endl;
            }
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(0, 0, 166, 144));
            animationCounter = (life < 2) ? 0 : animationCounter;
        }
    }

    void changeFrame(int timeLimit, int totalFrames, int width, int height)
    {
        if (animationClock.getElapsedTime().asMilliseconds() > timeLimit)
        {
            animationCounter = (animationCounter + 1) % totalFrames;
            sprite.setTextureRect(sf::IntRect(width * animationCounter, 0, width, height));
            animationClock.restart();
        }
    }

    void animation(RenderWindow& window)
    {
        if (life == 6 && !head)
        {
            changeTexture(2);
            head = true;
            headAnimationStep = 0;
        }

        if (life == 2)
        {
            changeTexture(3);
        }

        if (textureIndex == 0) // walk
        {
            changeFrame(200, 22, 166, 144);
        }
        else if (textureIndex == 1) // attack
        {
            changeFrame(200, (life < 6) ? 11 : 21, 166, 144);
        }
        else if (textureIndex == 2) // no head
        {
            changeFrame(200, 22, 166, 144);
        }
        else if (textureIndex == 3) // die
        {
            if (animationClock.getElapsedTime().asMilliseconds() > 50)
            {
                animationCounter++;
                if (animationCounter == 10)
                {
                    life -= 2;
                    dead = true;
                }
                sprite.setTextureRect(sf::IntRect(166 * animationCounter, 0, 166, 144));
                animationClock.restart();
            }
        }

        if (head)
        {
            if (headAnimationClock.getElapsedTime().asMilliseconds() > 200)
            {
                headAnimationStep++;
                if (headAnimationStep == 4)
                {
                    head = false;
                }
                headSprite.setTextureRect(sf::IntRect(150 * headAnimationStep, 0, 150, 186));
                headAnimationClock.restart();
            }
            headAnimationStep += 0.5;
            headSprite.setPosition(positionZ.x + headAnimationStep, positionZ.y);
            window.draw(headSprite);
        }
    }
};
