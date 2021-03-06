#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"
#include "TextureManager.h"
#include "Player.h"
#include "CreepSquad.h"
#include "DrawableTower.h"
#include "TextMessage.h"
#include "DrawableMap.h"
#include "DrawableCreepSquad.h"
#include "NearEndAttackStrategy.h"
#include "NearestAttackStrategy.h"
#include "StrongestAttackStrategy.h"
#include "WeakestAttackStrategy.h"
#include <vector>

class MainClass;

class Game {
public:
	Game(sf::RenderWindow* gameWindow, Map* map, TextureManager* tm, MainClass* m);

	void run();
	void update();
	void draw(sf::RenderWindow* w);

	bool isLevelCleared(); // will probably need parameters
	bool isGameOver(); // will probably need parameters

	void displayFinalScore(sf::RenderWindow* w);

private:
	sf::RenderWindow* gameWindow;
	Map* map;
	DrawableMap* drawable;
	TextureManager* tm;
	DrawableCreepSquad* creeps;
	Player* player;
	vector<DrawableTower*> towers;
	bool isRunning;
	int level;
	bool waveStarted;
	MainClass* main;


	//time variables
	sf::Time timeElapsed; //Keeps track of the time elapsed between update/draw calls
	sf::Time frameLength; //time needed for 60 frames per second
	sf::Clock programClock; //Clock to track time

	//ui handling
	Tower* selectedTower;
	enum INPUT_STATE{ SELECT_TOWER, TOWER_SELECTED, PLACE_TOWER };
	INPUT_STATE currentInputState;
	bool mouseClickedPrev;
	Tower::TOWER_TYPE towerTypeToBuild;
	sf::Sprite* towerPreview;
	bool previewTexSet = false;

	sf::Vector2i getMousePosition();
	void doInput();
	bool mouseClicked();

	sf::Vector2i buildRegLoc;
	sf::Vector2i buildIceLoc;
	sf::Vector2i buildCanLoc;
	sf::Vector2i buildSupLoc;
	sf::Vector2i upgradeTowerLoc;
	sf::Vector2i destroyTowerLoc;
	sf::Vector2i displayTowerSpriteLoc;
	sf::Vector2i cycleStratLoc;
	sf::Vector2i startWaveLoc;
	sf::Vector2i startWaveLoc2;

	void drawUI();

	//game over text
	TextMessage* gameOverText;
	TextMessage* moreGameOverText;
	TextMessage* evenMoreGameOverText;
	TextMessage* startWaveText;
	sf::RectangleShape* overlay;

	
	// text for panel to build towers
	TextMessage *regTowerText;
	TextMessage *iceTowerText;
	TextMessage *cannonTowerText;
	TextMessage *superTowerText;
	TextMessage *regTowerCostText;
	TextMessage *iceTowerCostText;
	TextMessage *cannonTowerCostText;
	TextMessage *superTowerCostText;

	// text for panel when tower is selected
	TextMessage *towerTypeText;
	TextMessage *towerDamageText;
	TextMessage *towerUpgradeCostText;
	TextMessage *towerRefundCostText;
	TextMessage *towerUpgradeLevelText;
	TextMessage *towerAttackStratText;
	TextMessage *upgradeText;
	TextMessage *destroyText;
	TextMessage *cycleStratText;

	// constant texts drawn
	TextMessage *levelText;
	TextMessage *healthText;
	TextMessage *coinsText;

	// sprites
	sf::Sprite* regTowerSprite;
	sf::Sprite* iceTowerSprite;
	sf::Sprite* cannonTowerSprite;
	sf::Sprite* superTowerSprite;
	sf::Sprite* destroyTowerIcon;
	sf::Sprite* upgradeTowerIcon;
	sf::Sprite* displayTowerIcon;
	sf::Sprite* cycleAttackIcon;
};