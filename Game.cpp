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
	creeps->resetCreepSquad(level, gameWindow);
	currentInputState = INPUT_STATE::SELECT_TOWER;

	frameLength = sf::milliseconds(1000 / 60); //time needed for 60 frames per second

	// create window according to the map size
	gameWindow->create(sf::VideoMode(map->getCols() * 24 + 20, (map->getRows() + 5 )* 24), "Tower Defense");

	// ui stuff
	mouseClickedPrev = false;
	selectedTower = NULL;
	currentInputState = INPUT_STATE::SELECT_TOWER;
	towerTypeToBuild = Tower::TOWER_TYPE::REGULAR;
	buildRegLoc = sf::Vector2i(1, map->getCols() + 1);
	buildIceLoc = sf::Vector2i(4, map->getCols() + 1);
	buildCanLoc = sf::Vector2i(1, map->getCols() + 3);
	buildSupLoc = sf::Vector2i(4, map->getCols() + 3);
	upgradeTowerLoc = sf::Vector2i(map->getRows() - 2, map->getCols() + 3);
	destroyTowerLoc = sf::Vector2i(map->getRows(), map->getCols() + 3);
	displayTowerSpriteLoc = sf::Vector2i(map->getRows() - 2, map->getCols() + 1);

	

	// text to be displayed on screen
	regTowerText = new TextMessage(tm, "Regular", sf::Vector2f(buildRegLoc.x * 24, buildRegLoc.y * 24 + 30));
	iceTowerText = new TextMessage(tm, "Ice", sf::Vector2f(buildIceLoc.x * 24, buildIceLoc.y * 24 + 30));
	cannonTowerText = new TextMessage(tm, "Cannon", sf::Vector2f(buildCanLoc.x * 24, buildCanLoc.y * 24 + 30));
	superTowerText = new TextMessage(tm, "Super", sf::Vector2f(buildSupLoc.x * 24, buildSupLoc.y * 24 + 30));
	upgradeText = new TextMessage(tm, "Upgrade", sf::Vector2f(upgradeTowerLoc.x * 24, upgradeTowerLoc.y * 24 + 30));
	destroyText = new TextMessage(tm, "Destroy", sf::Vector2f(destroyTowerLoc.x * 24, destroyTowerLoc.y * 24 + 30));
	towerTypeText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x * 24, displayTowerSpriteLoc.y * 24 + 5));
	towerUpgradeLevelText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x * 24, displayTowerSpriteLoc.y * 24 + 10));
	towerDamageText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x * 24, displayTowerSpriteLoc.y * 24 + 15));
	towerUpgradeCostText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x * 24, displayTowerSpriteLoc.y * 24 + 20));
	towerRefundCostText = new TextMessage(tm, "", sf::Vector2f(displayTowerSpriteLoc.x * 24, displayTowerSpriteLoc.y * 24 + 25));
	levelText = new TextMessage(tm, "Level " + to_string(level), sf::Vector2f(map->getRows() * 24 + 5, 10));
	healthText = new TextMessage(tm, "HP " + to_string(player->getHealth()), sf::Vector2f(map->getRows() * 24 + 5, 20));
	coinsText = new TextMessage(tm, "Coins " + to_string(player->getCoins()), sf::Vector2f(map->getRows() * 24 + 5, 30));

	// sprites to be displayed on screen
	regTowerSprite = new sf::Sprite();
	regTowerSprite->setTexture(tm->getTexture(TextureManager::TEXTURE::TOWER));
	regTowerSprite->setTextureRect(sf::IntRect(0, 0, 24, 24));
	regTowerSprite->setPosition(buildRegLoc.x * 24, buildRegLoc.y * 24);

	iceTowerSprite = new sf::Sprite();
	iceTowerSprite->setTexture(tm->getTexture(TextureManager::TEXTURE::TOWER));
	iceTowerSprite->setTextureRect(sf::IntRect(24, 0, 24, 24));
	iceTowerSprite->setPosition(buildIceLoc.x * 24, buildIceLoc.y * 24);

	cannonTowerSprite = new sf::Sprite();
	cannonTowerSprite->setTexture(tm->getTexture(TextureManager::TEXTURE::TOWER));
	cannonTowerSprite->setTextureRect(sf::IntRect(24*2, 0, 24, 24));
	cannonTowerSprite->setPosition(buildCanLoc.x * 24, buildCanLoc.y * 24);

	superTowerSprite = new sf::Sprite();
	superTowerSprite->setTexture(tm->getTexture(TextureManager::TEXTURE::TOWER));
	superTowerSprite->setTextureRect(sf::IntRect(24*3, 0, 24, 24));
	superTowerSprite->setPosition(buildSupLoc.x * 24, buildSupLoc.y * 24);

	destroyTowerIcon = new sf::Sprite();
	destroyTowerIcon->setTexture(tm->getTexture(TextureManager::TEXTURE::UI));
	destroyTowerIcon->setTextureRect(sf::IntRect(0, 0, 24, 24));
	destroyTowerIcon->setPosition(destroyTowerLoc.x * 24, destroyTowerLoc.y * 24);

	upgradeTowerIcon = new sf::Sprite();
	upgradeTowerIcon->setTexture(tm->getTexture(TextureManager::TEXTURE::UI));
	upgradeTowerIcon->setTextureRect(sf::IntRect(24, 0, 24, 24));
	upgradeTowerIcon->setPosition(upgradeTowerLoc.x * 24, upgradeTowerLoc.y * 24);
}

void Game::run() {
	isRunning = true;
	//update();
}

void Game::update() {

	while (isRunning) {
		timeElapsed += programClock.restart();

		if (timeElapsed >= frameLength){ //restrict to 60fps
			//process input
			doInput();

			//clear window
			gameWindow->clear();

			//creeps
			creeps->Update(player, gameWindow, timeElapsed);

			healthText->setMessage("HP " + to_string(player->getHealth()));
			coinsText->setMessage("Coins " + to_string(player->getCoins()));

			//towers
			for (int i = 0; i < towers.size(); ++i){
				towers[i]->Update(timeElapsed);
			}

			// draw window and all of the sprites, UI
			draw(gameWindow);
			//isRunning = gameWindow->isOpen();

			if (isGameOver()) 
				isRunning = false;
			
			if (isLevelCleared() && creeps->getStartingCreepList().empty()) {
				++level;
				levelText->setMessage("Level " + to_string(level));
				creeps->resetCreepSquad(level, gameWindow);
			}

			//reset timeElapsed
			timeElapsed = sf::Time::Zero;
		}
	}

	draw(gameWindow);
}

void Game::draw(sf::RenderWindow* w) {

	if (isRunning) 
	{
		w->clear();
		map->drawMap(w);
		creeps->Draw(w);

		for (int i = 0; i < towers.size(); ++i)
			towers[i]->Draw(gameWindow);
		drawUI();

		w->display();
	}
	else {
		displayFinalScore(w);
		// ask if user wants to play again, go back to menu, or exit
	}
}

bool Game::isLevelCleared() {
	//if level was cleared
	if (creeps->getCreeps().size() == 0)
		return true;
	else
		return false;
}

bool Game::isGameOver() {

	// if player's health is 0, return true
	if (player->getHealth() == 0)
		return true;
	else
		return false;
}

void Game::displayFinalScore(sf::RenderWindow* w) {
	string playerScore = "You made it to level " + std::to_string(level) + "!";
	// need to figure out coordinates for center of window
	TextMessage* finalScore = new TextMessage(tm, playerScore, sf::Vector2f(w->getSize().x / 2, w->getSize().y / 2));
	finalScore->drawMessage(w);
}

sf::Vector2i Game::getMousePosition(){
	//returns the "tile" position within the game screen
	//note - each tile is 24/24 pixels

	sf::Vector2i pos = sf::Mouse::getPosition(*gameWindow);

	int xPos = (pos.x / 24);
	int yPos = (pos.y / 24);

	return sf::Vector2i(xPos, yPos);
}

void Game::doInput(){
	if (mouseClicked()){
		sf::Vector2i mousePos = getMousePosition();
		cout << "Clicked mouse!\n";
		cout << mousePos.x << " " << mousePos.y << "\n";
	}
	
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

	// draw sprites
	gameWindow->draw(*regTowerSprite);
	gameWindow->draw(*iceTowerSprite);
	gameWindow->draw(*cannonTowerSprite);
	gameWindow->draw(*superTowerSprite);
	gameWindow->draw(*destroyTowerIcon);
	gameWindow->draw(*upgradeTowerIcon);

	// draw text
	regTowerText->drawMessage(gameWindow);
	iceTowerText->drawMessage(gameWindow);
	cannonTowerText->drawMessage(gameWindow);
	superTowerText->drawMessage(gameWindow);
	levelText->drawMessage(gameWindow);
	healthText->drawMessage(gameWindow);
	coinsText->drawMessage(gameWindow);

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