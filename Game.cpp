#include "Game.h"
#include "TextMessage.h"
#include "MainClass.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game(sf::RenderWindow* gameWindow, Map* map, TextureManager* tm, MainClass* m) {
	this->gameWindow = gameWindow;
	this->map = map;
	this->tm = tm;
	main = m;

	creeps = new CreepSquad(map, tm);
	player = new Player(tm, gameWindow);
	towers = vector<Tower*>();

	isRunning = false;
	level = 1;
	creeps->resetCreepSquad(level, gameWindow);
	currentInputState = INPUT_STATE::SELECT_TOWER;

	frameLength = sf::milliseconds(1000 / 60); //time needed for 60 frames per second

	// create window according to the map size
	gameWindow->create(sf::VideoMode((map->getCols() + 5) * 24, (map->getRows() + 8 )* 24), "Tower Defense");

	// ui stuff
	mouseClickedPrev = false;
	selectedTower = NULL;
	currentInputState = INPUT_STATE::SELECT_TOWER;
	towerTypeToBuild = Tower::TOWER_TYPE::REGULAR;
	buildRegLoc = sf::Vector2i(1, map->getCols() + 2);
	buildIceLoc = sf::Vector2i(4, map->getCols() + 2);
	buildCanLoc = sf::Vector2i(1, map->getCols() + 4);
	buildSupLoc = sf::Vector2i(4, map->getCols() + 4);
	upgradeTowerLoc = sf::Vector2i(map->getRows(), map->getCols() + 5);
	destroyTowerLoc = sf::Vector2i(map->getRows() + 3, map->getCols() + 5);
	displayTowerSpriteLoc = sf::Vector2i(map->getRows() + 1, map->getCols() + 1);


	// text to be displayed on screen
	regTowerText = new TextMessage(tm, "Regular", sf::Vector2f(buildRegLoc.x * 24, buildRegLoc.y * 24 + 30));
	iceTowerText = new TextMessage(tm, "Ice", sf::Vector2f(buildIceLoc.x * 24, buildIceLoc.y * 24 + 30));
	cannonTowerText = new TextMessage(tm, "Cannon", sf::Vector2f(buildCanLoc.x * 24, buildCanLoc.y * 24 + 30));
	superTowerText = new TextMessage(tm, "Super", sf::Vector2f(buildSupLoc.x * 24, buildSupLoc.y * 24 + 30));
	upgradeText = new TextMessage(tm, "Upgrade", sf::Vector2f(upgradeTowerLoc.x * 24 - 20, upgradeTowerLoc.y * 24 + 30));
	destroyText = new TextMessage(tm, "Destroy", sf::Vector2f(destroyTowerLoc.x * 24 - 20, destroyTowerLoc.y * 24 + 30));
	
	towerTypeText = new TextMessage(tm, "Hi", sf::Vector2f(displayTowerSpriteLoc.x * 24 - 60, displayTowerSpriteLoc.y * 24 + 10));
	towerUpgradeLevelText = new TextMessage(tm, "This", sf::Vector2f(displayTowerSpriteLoc.x * 24 - 60, displayTowerSpriteLoc.y * 24 + 25));
	towerDamageText = new TextMessage(tm, "Is", sf::Vector2f(displayTowerSpriteLoc.x * 24 - 60, displayTowerSpriteLoc.y * 24 + 40));
	towerUpgradeCostText = new TextMessage(tm, "Here", sf::Vector2f(displayTowerSpriteLoc.x * 24 - 60, displayTowerSpriteLoc.y * 24 + 55));
	towerRefundCostText = new TextMessage(tm, "!!!", sf::Vector2f(displayTowerSpriteLoc.x * 24 - 60, displayTowerSpriteLoc.y * 24 + 70));
	
	levelText = new TextMessage(tm, "Level " + to_string(level), sf::Vector2f(map->getRows() * 24 + 5, 10));
	healthText = new TextMessage(tm, "HP " + to_string(player->getHealth()), sf::Vector2f(map->getRows() * 24 + 5, 20));
	coinsText = new TextMessage(tm, "Coins " + to_string(player->getCoins()), sf::Vector2f(map->getRows() * 24 + 5, 30));

	gameOverText = new TextMessage(tm, "Game Over! :(", sf::Vector2f(0, 0));
	gameOverText->setScale(sf::Vector2f(2.0f, 3.0f));
	moreGameOverText = new TextMessage(tm, "You made it to level " + std::to_string(level), sf::Vector2f(0, 100));
	evenMoreGameOverText = new TextMessage(tm, "Press ENTER to return to menu...", sf::Vector2f(0, 150));

	overlay = new sf::RectangleShape(sf::Vector2f(gameWindow->getSize().x,gameWindow->getSize().y));
	overlay->setFillColor(sf::Color::Color(0, 0, 0, 200));


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

	displayTowerIcon = new sf::Sprite();
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

			if (isGameOver()){
				isRunning = false;
				moreGameOverText->setMessage("You made it to level " + std::to_string(level));
			}
			
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
	w->clear();
	map->drawMap(w);
	creeps->Draw(w);

	for (int i = 0; i < towers.size(); ++i)
		towers[i]->Draw(gameWindow);
	drawUI();
	
	if (!isRunning)
		displayFinalScore(w);	// Display final score and return to menu

	w->display();
	
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
	gameWindow->draw(*overlay);
	gameOverText->drawMessage(gameWindow);
	moreGameOverText->drawMessage(gameWindow);
	evenMoreGameOverText->drawMessage(gameWindow);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		main->switchToContext(MainClass::MENU);

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

		displayTowerIcon->setTexture(tm->getTexture(TextureManager::TEXTURE::TOWER));
		displayTowerIcon->setPosition(displayTowerSpriteLoc.x * 24 + 12, displayTowerSpriteLoc.y * 24);

		switch (selectedTower->getType()){
		case Tower::CANNON:
			towerTypeText->setMessage("Type: Cannon");
			displayTowerIcon->setTextureRect(sf::IntRect(0, 0, 24, 24));
			break;
		case Tower::ICE:
			towerTypeText->setMessage("Type: Ice");
			displayTowerIcon->setTextureRect(sf::IntRect(24, 0, 24, 24));
			break;
		case Tower::REGULAR:
			towerTypeText->setMessage("Type: Regular");
			displayTowerIcon->setTextureRect(sf::IntRect(24 * 2, 0, 24, 24));
			break;
		case Tower::SUPER:
			towerTypeText->setMessage("Type: Super");
			displayTowerIcon->setTextureRect(sf::IntRect(24 * 3, 0, 24, 24));
			break;
		}

		towerUpgradeLevelText->setMessage("Tower Level: " + to_string(selectedTower->getUpgradeLevel()));
		towerDamageText->setMessage("Damage: " + to_string(selectedTower->getDamage()));
		towerUpgradeCostText->setMessage("Upgrade Cost: " + to_string(selectedTower->getUpgradeCost()));
		towerRefundCostText->setMessage("Refund Cost: " + to_string(selectedTower->getRefund()));

		if (mouseClicked()){
			sf::Vector2i mPos = getMousePosition();
			bool didSomething = false;

			//upgrade tower
			if (mPos == upgradeTowerLoc){
				if ((player->getCoins() - selectedTower->getUpgradeCost()) >= 0){
					player->setCoins(player->getCoins() - selectedTower->getUpgradeCost());
					selectedTower->setUpgradeLevel(selectedTower->getUpgradeLevel() + 1);
				}
				didSomething = true;
				break;
			}

			//destroy tower
			if (mPos == destroyTowerLoc){
				player->setCoins(player->getCoins() + selectedTower->getRefund());
				
				towers.erase(std::remove(towers.begin(), towers.end(), selectedTower), towers.end());

				delete selectedTower;
				selectedTower = NULL;
				currentInputState = INPUT_STATE::SELECT_TOWER;
				didSomething = true;
				break;
			}

			//click on another tower
			for (int i = 0; i < towers.size(); ++i){
				if ((towers[i]->getMapPosition()) == mPos){
					selectedTower = towers[i];
					didSomething = true;
					break;
				}
			}

			//clicked on environment
			if (!didSomething){
				selectedTower = NULL;
				currentInputState = INPUT_STATE::SELECT_TOWER;
				break;
			}
		}
		break;

	case PLACE_TOWER:
		if (mouseClicked()){
			sf::Vector2i mPos = getMousePosition();

			//Lots of stupidty involving getting the map coordinates
			//for whatever reason, getTile has x and y inversed...
			//for now, just switching the x and y when calling
			if (map->getTile(mPos.y, mPos.x) == Map::ENV &&
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

	if (currentInputState == TOWER_SELECTED) {
		// doesnt work
		towerTypeText->drawMessage(gameWindow);
		towerUpgradeLevelText->drawMessage(gameWindow);
		towerDamageText->drawMessage(gameWindow);
		towerUpgradeCostText->drawMessage(gameWindow);
		towerRefundCostText->drawMessage(gameWindow);

		//works
		upgradeText->drawMessage(gameWindow);
		destroyText->drawMessage(gameWindow);
		//gameWindow->draw(*displayTowerIcon);
	}

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

}