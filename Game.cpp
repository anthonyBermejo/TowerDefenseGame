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
	player = new Player(tm);
	towers = vector<Tower*>();

	isRunning = false;
	level = 1;

	frameLength = sf::milliseconds(1000 / 60); //time needed for 60 frames per second

	//reset window size to match that of the map
	sf::Vector2u windowSize(map->getCols()*24, map->getRows()*24);
	gameWindow->setSize(windowSize);

	//ui stuff
	mouseClickedPrev = false;
	selectedTower = NULL;
	currentInputState = INPUT_STATE::SELECT_TOWER;
	towerTypeToBuild = Tower::TOWER_TYPE::REGULAR;
	buildRegLoc = sf::Vector2i(10, 10);
	buildIceLoc = sf::Vector2i(10, 10);
	buildCanLoc = sf::Vector2i(10, 10);
	buildSupLoc = sf::Vector2i(10, 10);
	upgradeTowerLoc = sf::Vector2i(10, 10);
	destroyTowerLoc = sf::Vector2i(10, 10);
}

void Game::run() {
	isRunning = true;
	update();
}

void Game::update() {
	while (isRunning) {
		timeElapsed += programClock.restart();

		if (timeElapsed >= frameLength){//restrict to 60fps
			//process input
			doInput();
			
			
			//clear window
			gameWindow->clear();


			//draw map
			map->drawMap(gameWindow);

			//update
			//creeps
			creeps->move(player, gameWindow);

			//towers
			for (int i = 0; i < towers.size(); ++i){
				towers[i]->Update(timeElapsed);
				towers[i]->Draw(gameWindow);
			}


			// show everything!
			draw(gameWindow);
			isRunning = gameWindow->isOpen();
			if (gameOver(creeps)) {
				isRunning = false;
			}
			else if (levelCleared(creeps))
				++level;

			//reset timeElapsed
			timeElapsed = sf::Time::Zero;
		}
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

sf::Vector2i Game::getMousePosition(){
	//returns the "tile" position within the game screen
	//note - each tile is 24/24 pixels
	
	sf::Vector2i pos = sf::Mouse::getPosition(*gameWindow);

	int xPos = (pos.x / 24) * 24;
	int yPos = (pos.y / 24) * 24;

	return sf::Vector2i(xPos, yPos);
}

void Game::doInput(){
	switch (currentInputState){
	case SELECT_TOWER:
		if (mouseClicked()){
			sf::Vector2i mPos = getMousePosition();
			
			//check if selected tower
			for (int i = 0; i < towers.size(); ++i){
				if ((towers[i]->getMapPosition()) == mPos){
					selectedTower = towers[i];
					currentInputState = INPUT_STATE::TOWER_SELECTED;
					break;
				}
			}

			//check if clicked on build regular
			if (mPos == buildRegLoc){
				towerTypeToBuild = Tower::REGULAR;
				currentInputState = INPUT_STATE::PLACE_TOWER;
				break;
			}

			//check if clicked on build ice
			if (mPos == buildIceLoc){
				towerTypeToBuild = Tower::ICE;
				currentInputState = INPUT_STATE::PLACE_TOWER;
				break;
			}

			//check if clicked on build cannon
			if (mPos == buildCanLoc){
				towerTypeToBuild = Tower::CANNON;
				currentInputState = INPUT_STATE::PLACE_TOWER;
				break;
			}

			//check if clicked on build super
			if (mPos == buildSupLoc){
				towerTypeToBuild = Tower::SUPER;
				currentInputState = INPUT_STATE::PLACE_TOWER;
				break;
			}

		}
		break;

	case TOWER_SELECTED:
		if (mouseClicked()){
			sf::Vector2i mPos = getMousePosition();

			//upgrade tower
			if (mPos == upgradeTowerLoc && (player->getCoins() - selectedTower->getUpgradeCost()) >= 0){
				player->setCoins(player->getCoins() - selectedTower->getUpgradeCost());
				selectedTower->setUpgradeLevel(selectedTower->getUpgradeLevel() + 1);
				break;
			}

			//destroy tower
			if (mPos == destroyTowerLoc){
				towers.erase(std::remove(towers.begin(), towers.end(), selectedTower), towers.end());
				selectedTower = NULL;
				currentInputState = INPUT_STATE::SELECT_TOWER;
				break;
			}

			//clicked on environment
			selectedTower = NULL;
			currentInputState = INPUT_STATE::SELECT_TOWER;
			break;
		}
		break;

	case PLACE_TOWER:
		if (mouseClicked()){
			sf::Vector2i mPos = getMousePosition();
			if (map->getTile(mPos.x, mPos.y) == Map::ENV &&
				(player->getCoins() - Tower::getTowerTypeCost(towerTypeToBuild)) >= 0){
				
				//search if tower already exists in that place
				bool found = false;
				for (int i = 0; !found && i < towers.size(); ++i)
					if (mPos == towers[i]->getMapPosition())
						found = true;

				if (!found){//YOU CAN BUILD IT :D
					Tower* t = new Tower(towerTypeToBuild, 1, mPos, creeps, player, tm);
					towers.push_back(t);
					currentInputState = INPUT_STATE::SELECT_TOWER;
					player->setCoins(player->getCoins() - t->getCost());
					break;
				}
				else{
					//can offord but tower already exists
					currentInputState = INPUT_STATE::SELECT_TOWER;
					break;
				}
			}
			else{
				//not placed in environment or cannot offord
				currentInputState = INPUT_STATE::SELECT_TOWER;
				break;
			}
		}

		break;

	}
	
	//set prevMouseClicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
		if (!mouseClickedPrev)
			mouseClickedPrev = true;
	}
	else
		mouseClickedPrev = false;

}

bool Game::mouseClicked(){
	return !mouseClickedPrev && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Game::drawUI(){
	switch (currentInputState){
		
	}
}