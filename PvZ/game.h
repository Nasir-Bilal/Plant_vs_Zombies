
#include "iostream"
#include "Levels/levels.h"
#include "Levels/level1.h"
#include "mainMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

class Game
{
private:
	
	sf::RenderWindow window;
	MainMenu mainMenu;
	int menuState;
	int currentScreen;
	coordinats mouse, mouseClick, boxClicked;
	Levels* levelNum;
	sf::Clock zGeneratClock;
	sf::RectangleShape dummyRect;
public:
	//VideoMode::getDesktopMode()
	//VideoMode(1200, 700)
	Game() : window(VideoMode(1200, 700), "Plants Vs Zombies"), mainMenu("../SFML/Images/Menu/back.jpeg"),
		mouse(0, 0), menuState(0), levelNum(nullptr), currentScreen(MenuState::MainMenu)//menuState(1), levelNum(new Level1)//
	{
		dummyRect.setSize(Vector2f(100, 100));
		dummyRect.setFillColor(Color(255, 255, 255, 100));
		dummyRect.setPosition(230, 130);

	}
	void setMenuState(const int s)
	{
		menuState = s;
		
	}
	int start()
	{
		window.setPosition(Vector2i(0, 0));
		window.setFramerateLimit(60);

		//Game icon
		Image icon;
		if (!icon.loadFromFile("../SFML/Images/icon.png"))
		{
			return 1;
		}
		window.setIcon(32, 32, icon.getPixelsPtr());

		///////////////////////////////////////

		int check;//??
		Clock clock;//main click
		Clock timeMoney; //????
		bool isMousePressed = false; // to detect click and release
		int gridX, gridY;

		
		while (window.isOpen())
		{


			float time = clock.getElapsedTime().asMicroseconds();
			float moneyTime = timeMoney.getElapsedTime().asSeconds();

			clock.restart();
			time = time / 800;

			sf::Event event;

		\
			while (window.pollEvent(event))
			{
				//window closing conditions
				if (event.type == Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
				//mouse move
				if (event.type == sf::Event::MouseMoved)
				{
					//mainMenu.handleInputs(event, window);
				}
				//mouse click
				if (event.type == sf::Event::MouseButtonPressed && menuState == 0)
				{
					
					mouse.x = event.mouseButton.x;
					mouse.y = event.mouseButton.y;
					//cout << "(" << mouse.x << ',' << mouse.y << ')' << endl;
				}
				//will probably add this in update function
				if (menuState == 1)
				{
					//mouse left pressed
					//if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
					//{
					//	isMousePressed = true;
					//		mouseClick.x = event.mouseButton.x;
					//		mouseClick.y = event.mouseButton.y;
					//		if ((mouse.x >= 0 && mouse.x <= 522) && (mouse.y >= 0 && mouse.y <= 90))
					//		{
					//			mouseClick.x = (mouse.x);
					//			mouseClick.y = (mouse.y);
					//			cout << "click (" << mouseClick.x << ',' << mouseClick.y << ')' << endl;
					//			shopClicked = true;

					//		}
					//	//cout << "(" << mouseX << ',' << mouseY << ')' << endl;
					//}
					//// Mouse button released
					//if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
					//{
					//	mouse.x = event.mouseButton.x;// event.mouseButton.x; 
					//	mouse.y = event.mouseButton.y;//event.mouseButton.y;
					//	cout << "(" << mouse.x << ',' << mouse.y << ')' << endl;
					//	
					//	if((mouse.x>=230 && mouse.x<=1109) && (mouse.y>=130 && mouse.y<=550 ))
					//	{
					//		boxClicked.x = ((mouse.x) - 280.0)/92.0;
					//		boxClicked.y = (mouse.y - 130) / 110;

					//		cout << "BOX  of grid clicked (" << boxClicked.x << ',' << boxClicked.y << ')' << endl;	
					//		gridClicked = true;

					//	}
					//}	
					//if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
					//{
					//	
					//}
				}
			}

			window.clear();
			//mygame.createBack(window);
			/*if (levelNum)
			{
				levelNum->update(0,0,1,1);
			}*/
			//updateGrid(event,window);
			display(window);
			handleInputsAndEvents(event, window);

			//window.draw(levelNum->myShop.getShopSprite());
			window.display();
		}

	}
	void updateState() {
		// Example of switching states and initializing levels
		if (menuState == MenuState::LevelSelection && levelNum == nullptr) {
			delete levelNum;  // Ensure to clean up existing level if any
			levelNum = new Level1();  // Dynamically allocate the new level or screen
		}
		else if (menuState == MenuState::HighScore) {
			// Initialize high score screen; ensure it's properly managed
		}
		// Further state initializations...
	}

	void display(RenderWindow& window)
	{
		// Main Menu menuState
		if (menuState == 0)
		{
			//mainMenu.draw(window);
			mainMenu.render(window);
		}
		// level 1 menuState lolol
		else if (levelNum)
		{
			levelNum->createZombie(zGeneratClock);
			levelNum->renderDisplay(window);
		}

	}
	
	void handleInputsAndEvents(sf::Event& event, sf::RenderWindow& window)
	{
		
		if (menuState == MenuState::MainMenu)
		{
			mainMenu.handleInputs(event, window);
			mainMenu.handleEvent(window, event);
		}

		int potentialNextState = mainMenu.getNextState();
		if (potentialNextState != -1) {
			transitionState(potentialNextState);
			mainMenu.resetNextState();  // Reset the state in main menu after handling
		}
		if (levelNum && menuState == MenuState::LevelSelection)
		{
			levelNum->update(event,window);
			levelNum->updateGrid(event, window);
		}
	}
	void transitionState(int newState)
	{
		if (menuState != newState) {
			// Clean up current state if necessary
			if (levelNum != nullptr) {
				delete levelNum;
				levelNum = nullptr;
			}
			menuState = newState;  // Update the state
			if (menuState == MenuState::LevelSelection) 
			{
				levelNum = new Level1();  // Only instantiate the new level when needed
			}
			// Additional state initialization
		}
	}
};