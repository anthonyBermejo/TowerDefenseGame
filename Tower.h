#ifndef TOWER_H
#define TOWER_H

#include<SFML/Graphics.hpp>
#include "CreepSquad.h"
#include "TextureManager.h"

class Tower{

public:
	/*
	Ice Tower slows down creeps
	Cannon causes AoE damage
	Regular is boring
	Super is a combination of Cannon and Ice
	*/
	enum TOWER_TYPE{ ICE, CANNON, REGULAR, SUPER };

	Tower(TOWER_TYPE type, int level, sf::Vector2i mapPos, CreepSquad* squad,Player* p,TextureManager* tm);
	~Tower();

	//getters
	//----------------------------------------
	int getCost() const;
	int getRefund() const;
	int getRange() const;
	int getDamage() const;
	int getUpgradeLevel() const;
	bool isCoolingDown() const;
	sf::Vector2i getMapPosition() const;
	TOWER_TYPE getType() const;
	sf::Time getCooldownTime() const;
	int getUpgradeCost() const;
	sf::Sprite getSprite() const;

	static int getTowerTypeCost(TOWER_TYPE);

	//setters
	//----------------------------------------
	void setUpgradeLevel(int level);

	//other functions
	//----------------------------------------
	void Update(sf::Time elapsedTime); //elapsedTime being the time passed since last update

	void Draw(sf::RenderWindow* w);


private:
	//members
	//----------------------------------------
	int cost;
	int refund;
	int range;
	int baseDamage;
	int upgradeLevel;
	const TOWER_TYPE type;

	sf::Time cooldownTime;
	sf::Time cooldownElapsed;
	bool coolingDown;

	const sf::Vector2i mapPosition;
	
	CreepSquad* squad;

	TextureManager* tm;
	sf::Sprite sprite;

	Player* p;

	//functions
	//----------------------------------------

	void shootAvailableCreeps();

};
#endif