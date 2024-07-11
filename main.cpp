#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"

using namespace sf;


float offsetX = 0, offsetY = 0;


int main()
{
	RenderWindow window(VideoMode(600, 400), "cute cat");

	menu(window);

	return 0;
}

