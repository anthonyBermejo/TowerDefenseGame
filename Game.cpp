#include "Game.h"
#include "TextMessage.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game(sf::RenderWindow* gameWindow, Map* map, TextureManager* tm) {
	this->gameWindow = gameWindow;
	this->map = map;
	this->tm = tm;

	creeps = new CreepSquad(map, tm);
	player = new Player();
	towers = vector<Tower*>();

	isRunning = false;
	level = 1;
}

void Game::run() {
	isRunning = true;
	update();
}

void Game::update() {
	while (isRunning) {
		// show everything!
		draw(gameWindow);
		isRunning = gameWindow->isOpen();
		if (gameOver(creeps)) {
			isRunning = false;
		}
		else if (levelCleared(creeps))
			++level;
	}
	draw(gameWindow);
}

void Game::draw(sf::RenderWindow* w) {
// I don't know, maybe?
	if (isRunning) {
		w->clear();
		map->drawMap(w);
		creeps->move(player, w);
		if (towers.size() > 0) {
			// tower stuff
		}
		w->display();
	}
	else {
		displayFinalScore(w);
		// ask if user wants to play again, go back to menu, or exit
	}
}

bool Game::levelCleared(CreepSquad* creeps) {
	//if level was cleared
		// return true;
	return false;
}

bool Game::gameOver(CreepSquad* creeps) {
	
	//if game is over
		// return true;
	return false;
}

void Game::displayFinalScore(sf::RenderWindow* w) {
	string playerScore = "You made it to level " + std::to_string(level) + "!";
	// need to figure out coordinates for center of window
	TextMessage* finalScore = new TextMessage(tm, playerScore, sf::Vector2f(25.0f, 25.0f));

	w->clear();
	finalScore->drawMessage(w);
	w->display();
}