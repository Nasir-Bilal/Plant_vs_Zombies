
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "coordinates.h"
#include <ctime>

using namespace sf;
using namespace std;


const coordinats topLeftPlayingArea(280, 130);

int main()
{
	srand(time(0));
	Game myGame;

	myGame.start();

	return 0;
}