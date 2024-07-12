#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Map.h"


using namespace sf;

extern bool pick_up;

void game(RenderWindow& window);