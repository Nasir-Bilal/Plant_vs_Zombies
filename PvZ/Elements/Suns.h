#pragma once
#include "iostream"
#include "../coordinates.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

class Suns {
private:
	sf::Image sunImage;
	sf::Sprite sunSprite;
	sf::Texture sunTexture;
	sf::IntRect sunSourceRect;
	int currentFrame;
	int numFrames;
	float frameDuration;
	sf::Clock frameClock;
	sf::Clock sunClock;
	coordinats position;
	int currentY;
	bool isDropping;
	float dropSpeed;
public:
	Suns() : sunSourceRect(0, 0, 71, 71), isDropping(false), dropSpeed(1.0f)
	{
		//loading image
		if (!sunImage.loadFromFile("../SFML/Images/Spritesheets/sun.png")) {
			// Error handling: unable to load image
			std::cerr << "Failed to load frame sheet image!" << std::endl;
			// You may add additional error handling or throw an exception here
		}
		sunTexture.loadFromImage(sunImage);
		sunSprite.setTexture(sunTexture);
		sunSprite.setTextureRect(sunSourceRect);
		//setting random position
		//position.x = getRandomInt(260, 987);//x axis aka columns
		//position.x = getRandomInt(110, 600);//y axis aka rows
		position.x = std::rand() % 739 + 260;//x axis
		position.y = std::rand() % 490 + 110;//y axis
		currentY = 0;

		//std::cout << "Sun: (" << position.x << ", " << position.y << std::endl;
		sunSprite.setOrigin(0, 0);
		sunSprite.setPosition(position.x, currentY);

		//setting frame details
		currentFrame = 0;
		numFrames = 22;
		frameDuration = 80.0f; // adjust as needed
		frameClock.restart();
		sunClock.restart();
	}
	void displayAndUpdateAnimation()
	{
		if (frameClock.getElapsedTime().asMilliseconds() >= frameDuration) //(frameClock.getElapsedTime().asMicroseconds() >= frameDuration) {
		{
			currentFrame = (currentFrame + 1) % numFrames;
			sunSourceRect.left = currentFrame * 71;
			sunSprite.setTextureRect(sunSourceRect);
			frameClock.restart();
		}
	}
	sf::Sprite getSunSprite() const
	{
		return sunSprite;
	}
	bool isExpired() const {
		return sunClock.getElapsedTime().asSeconds() >= 17.0;
	}

	bool isClicked(sf::RenderWindow& window, coordinats mouse) const {
		// Convert mouse x and y coordinates to world coordinates (relative to the window)
		float worldMouseX = window.mapPixelToCoords(sf::Vector2i(mouse.x, mouse.y)).x;
		float worldMouseY = window.mapPixelToCoords(sf::Vector2i(mouse.x, mouse.y)).y;

		// Get the global bounding rectangle of the sprite
		sf::FloatRect spriteBounds = sunSprite.getGlobalBounds();

		// Check if the mouse coordinates are within the bounds of the sprite
		if (spriteBounds.contains(worldMouseX, worldMouseY)) {
			return true; // Sun is clicked
		}

		return false; // Sun is not clicked
	}
	void startDropping()
	{
		isDropping = true;
	}
	void dropSun()
	{
		if (isDropping)
		{
			// Move the sun downwards
			currentY += dropSpeed;
			sunSprite.setPosition(position.x, currentY);

			// Check if the sun has reached the target position
			if (currentY >= position.y) {
				// Stop dropping
				isDropping = false;
			}
		}
	}
	sf::Clock getSunClock()const
	{
		return sunClock;
	}
	void setPosition(coordinats pos)
	{
		sunSprite.setPosition(pos.x, pos.y);
	}
};