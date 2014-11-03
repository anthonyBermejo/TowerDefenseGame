#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"
#include "TextureManager.h"
#include "Player.h"
#include "CreepSquad.h"
#include "Tower.h"
#include <vector>

class Game {
public:
	Game(sf::RenderWindow* gameWindow, Map* map, TextureManager* tm);

	void run();
	void update();
	void draw(sf::RenderWindow* w);

	bool levelCleared(CreepSquad* creeps); // will probably need parameters
	bool gameOver(CreepSquad* creeps); // will probably need parameters

	void displayFinalScore(sf::RenderWindow* w);

private:
	sf::RenderWindow* gameWindow;
	Map* map;
	TextureManager* tm;
	CreepSquad* creeps;
	Player* player;
	vector<Tower*> towers;
	bool isRunning;
	int level;

	//time variables
	sf::Time timeElapsed; //Keeps track of the time elapsed between update/draw calls
	sf::Time frameLength; //time needed for 60 frames per second
	sf::Clock programClock; //Clock to track time

};