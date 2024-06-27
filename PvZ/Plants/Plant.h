#pragma once
#include "iostream"
#include "../coordinates.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace std;

class Plant {
public:
	sf::Image plantImage;
	sf::Sprite plantSprite;
	sf::Texture plantTexture;
	sf::IntRect plantSourceRect;
	int currentFrame;
	int numFrames;
	float frameDuration;
	sf::Clock frameClock;
	string namePlant;
	int costPlant;
	int currentHealth; // keep track of health left
	int lifePlant; // total health?
	coordinats coord;
	int plantId;
public:
	Plant(int c, int r, int id) :coord(c, r), plantSourceRect(0, 0, 90, 110), currentHealth(100),
		plantId(id) { }
	virtual void displayAndUpdateAnimation() = 0;

};
