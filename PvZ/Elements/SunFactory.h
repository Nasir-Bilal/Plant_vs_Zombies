#pragma once
#include "iostream"
#include "Suns.h"
#include "../coordinates.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <random>

struct sunNode {
	sunNode* nextSun;
	Suns sun;
	//default
	sunNode() : nextSun(nullptr) {}
	//parameterized
	sunNode(const Suns& sunObj) : sun(sunObj), nextSun(nullptr) {}
};

class SunFactory {
public:
	sf::Font font;
	sf::Text text;
	sf::RectangleShape background;
	sf::FloatRect textBounds;
	std::string currencyString;

	sunNode* startSun;
	int sunCount;
	int sunCurrency;
	sf::Clock createClock;

public:
	SunFactory() : startSun(nullptr), sunCount(0), sunCurrency(50) 
	{
		if (!font.loadFromFile("../SFML/Fonts/SamdanEvil.ttf")) {
			// Handle error
			std::cerr << "Error loading font" << std::endl;
			return;
		}

		updateCurrencyText();
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Black);
		text.setPosition(30, 58);

		// Create a background rectangle for the text
		background.setFillColor(sf::Color(245, 245, 220)); // Beige color
		updateBackground();
	}
	~SunFactory() {
		deleteAllSuns(); // Cleaning up
	}
	void createSun()
	{
		//Suns newSun;
		sunNode* newNode = new sunNode;
		newNode->sun.startDropping();

		if (startSun == nullptr)
		{
			startSun = newNode;
		}
		else
		{
			sunNode* current = startSun;
			while (current->nextSun != nullptr)
			{
				current = current->nextSun;
			}
			current->nextSun = newNode;
		}
		sunCount++;
	}
	void createSun(coordinats position)
	{
		//Suns newSun;
		cout << "create sun sunfac" << endl;
		sunNode* newNode = new sunNode;
		newNode->sun.setPosition(position);

		if (startSun == nullptr)
		{
			startSun = newNode;
		}
		else
		{
			sunNode* current = startSun;
			while (current->nextSun != nullptr)
			{
				current = current->nextSun;
			}
			current->nextSun = newNode;
			current->nextSun->sun.setPosition(position);
		}
		sunCount++;
	}
	void deleteSun()
	{
		if (startSun != nullptr)
		{
			sunNode* temp = startSun;
			startSun = startSun->nextSun;
			delete temp;
			sunCount--;
		}
	}
	void deleteAllSuns()
	{
		while (startSun != nullptr)
		{
			sunNode* temp = startSun;
			startSun = startSun->nextSun;
			delete temp;
		}
		sunCount = 0;
	}
	void renderSuns(sf::RenderWindow& window)
	{
		sunNode* current = startSun;
		while (current != nullptr)
		{
			window.draw(current->sun.getSunSprite());
			current->sun.displayAndUpdateAnimation();
			current = current->nextSun;
		}
	}
	void update()
	{
		// create sun every 10 seconds
		if (createClock.getElapsedTime().asSeconds() >= 4) {
			createSun();
			createClock.restart(); // Reset the create clock
		}
		//logic to delete expired suns
		sunNode* current = startSun;
		sunNode* prev = nullptr;
		while (current != nullptr)
		{
			//current->sun.getSunClock().restart(); // Reset the clock for each sun
			if (current->sun.isExpired())
			{
				sunNode* temp = current;
				if (prev != nullptr)
				{
					prev->nextSun = current->nextSun;
				}
				else
				{
					startSun = current->nextSun;
				}
				current = current->nextSun;
				delete temp;
				sunCount--;
			}
			else {
				prev = current;
				current = current->nextSun;
			}
		}
		//checkClick(window);
	}
	void dropAllSuns()
	{
		sunNode* current = startSun;
		while (current != nullptr)
		{
			current->sun.dropSun();
			current = current->nextSun;
		}
	}
	void checkClick(sf::RenderWindow& window, coordinats mouse)
	{
		sunNode* current = startSun;
		sunNode* previous = nullptr;

		while (current != nullptr)
		{
			if (current->sun.isClicked(window, mouse))
			{
				// If the clicked sun is the first node
				if (previous == nullptr)
				{
					startSun = current->nextSun;
					delete current;
					current = startSun; // Move to the next node
				}
				else
				{
					previous->nextSun = current->nextSun;
					delete current;
					current = previous->nextSun; // Move to the next node
				}
				sunCurrency += 25;
				updateCurrencyText();
			}
			else
			{
				previous = current;
				current = current->nextSun;
			}
		}
	}
	void updateCurrencyText()
	{
		text.setString(std::to_string(sunCurrency));
		updateBackground();
	}
	void updateBackground() 
	{
		sf::FloatRect textBounds = text.getLocalBounds();
		float paddingX = 20; // Horizontal padding
		float paddingY = 1; // Vertical padding
		background.setSize(sf::Vector2f(textBounds.width + paddingX * 2, textBounds.height + paddingY * 2)); // Add horizontal padding on both sides
		background.setPosition(text.getPosition().x + textBounds.left - paddingX, text.getPosition().y + textBounds.top - paddingY);
	}
	void renderCurrency(sf::RenderWindow& window)
	{
		window.draw(background);
		window.draw(text);
	}
};