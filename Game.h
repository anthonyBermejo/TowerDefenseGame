#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"
#include "TextureManager.h"

class Game{
public:
	Game();

	void run();
	void update();
	void draw(sf::RenderWindow* w);

private:
	sf::RenderWindow gameWindow;
	Map* map;
	TextureManager* tm;


};