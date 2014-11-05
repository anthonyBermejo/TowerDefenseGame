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
	player = new Player(tm, gameWindow);
	towers = vector<Tower*>();

	isRunning = false;
	level = 1;

	frameLength = sf::milliseconds(1000 / 60); //time needed for 60 frames per second

	//reset window size to match that of the map
	sf::Vector2u windowSize(map->getCols() * 24, map->getRows() * 24);
	gameWindow->setSize(windowSize);

	//ui stuff
	mouseClickedPrev = false;
	selectedTower = NULL;
	currentInputState = INPUT_STATE::SELECT_TOWER;
	towerTypeToBuild = Tower::TOWER_TYPE::REGULAR;
	buildRegLoc = sf::Vector2i(1, map->getCols() + 1);
	buildIceLoc = sf::Vector2i(3, map->getCols() + 1);
	buildCanLoc = sf::Vector2i(1, map->getCols() + 3);
	buildSupLoc = sf::Vector2i(3, map->getCols() + 3);
	upgradeTowerLoc = sf::Vector2i(map->getRows() - 3, map->getCols() + 3);
	destroyTowerLoc = sf::Vector2i(map->getRows() - 1, map->getCols() + 3);
	displayTowerSpriteLoc = sf::Vector2i(map->getRows() - 2, map->getCols() + 1);

	regTowerText = new TextMessage(tm, "Regular", sf::Vector2f(buildRegLoc.x, buildRegLoc.y * 24 + 10));
	iceTowerText = new TextMessage(tm, "Ice", sf::Vector2f(buildRegLoc.x, buildRegLoc.y * 24 + 10));
	cannonTowerText = new TextMessage(tm, "Cannon", sf::Vector2f(buildRegLoc.x, buildRegLoc.y * 24 + 10));
	superTowerText = new TextMessage(tm, "Super", sf::Vector2f(buildRegLoc.x, buildRegLoc.y * 24 + 10));
	upgradeText = new TextMessage(tm, "Upgrade", sf::Vector2f(upgradeTowerLoc.x, upgradeTowerLoc.y * 24 + 10));
	destroyText = new TextMessage(tm, "Destroy", sf::Vector2f(destroyTowerLoc.x, destroyTowerLoc.y * 24 + 10));


	towerTypeText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x, displayTowerSpriteLoc.y + 5));
	towerUpgradeLevelText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x, displayTowerSpriteLoc.y + 10));
	towerDamageText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x, displayTowerSpriteLoc.y + 15));
	towerUpgradeCostText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x, displayTowerSpriteLoc.y + 20));
	towerRefundCostText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x, displayTowerSpriteLoc.y + 25));
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

			//update logic

			//creeps
			creeps->Update(player, gameWindow, timeElapsed);
			creeps->Draw(gameWindow);

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
		//creeps->move(player, w);
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

			switch (selectedTower->getType()){
			case Tower::CANNON:
				towerTypeText->setMessage("Type: Cannon");
				break;
			case Tower::ICE:
				towerTypeText->setMessage("Type: Ice");
				break;
			case Tower::REGULAR:
				towerTypeText->setMessage("Type: Regular");
				break;
			case Tower::SUPER:
				towerTypeText->setMessage("Type: Super");
				break;
			}

			towerUpgradeLevelText->setMessage("Tower Level: " + to_string(selectedTower->getUpgradeLevel()));
			towerDamageText->setMessage("Damage: " + to_string(selectedTower->getDamage()));
			towerUpgradeCostText->setMessage("Upgrade Cost: " + to_string(selectedTower->getUpgradeCost()));
			towerRefundCostText->setMessage("Refund Cost: " + to_string(selectedTower->getRefund()));

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

	regTowerText->drawMessage(gameWindow);
	iceTowerText->drawMessage(gameWindow);
	cannonTowerText->drawMessage(gameWindow);
	superTowerText->drawMessage(gameWindow);

	switch (currentInputState){
	case SELECT_TOWER: // state to create a tower
		break;
	case TOWER_SELECTED: // state when a tower is selected
		towerTypeText->drawMessage(gameWindow);
		towerUpgradeLevelText->drawMessage(gameWindow);
		towerDamageText->drawMessage(gameWindow);
		towerUpgradeCostText->drawMessage(gameWindow);
		towerRefundCostText->drawMessage(gameWindow);
		upgradeText->drawMessage(gameWindow);
		destroyText->drawMessage(gameWindow);
		break;
	}
}