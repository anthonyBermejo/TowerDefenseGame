#ifndef TOWER_H
#define TOWER_H

#include<SFML/Graphics.hpp>
#include "CreepSquad.h"
#include "TextureManager.h"
#include "AttackStrategy.h"

using namespace std;

class Tower{

public:
	/*
	Ice Tower slows down creeps
	Cannon causes AoE damage
	Regular is boring
	Super is a combination of Cannon and Ice
	*/
	enum TOWER_TYPE{ ICE, CANNON, REGULAR, SUPER };

	Tower(TOWER_TYPE type, int level, sf::Vector2i mapPos, CreepSquad* squad,Player* p);
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
	sf::Vector2i getEndPointPosition() const;
	TOWER_TYPE getType() const;
	sf::Time getCooldownTime() const;
	int getUpgradeCost() const;

	static int getTowerTypeCost(TOWER_TYPE);

	//setters
	//----------------------------------------
	void setUpgradeLevel(int level);

	//other functions
	//----------------------------------------
	void Update(sf::Time elapsedTime); //elapsedTime being the time passed since last update

	void setAttackStrategy(AttackStrategy* strat);


protected:
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
	const sf::Vector2i endPointPosition;
	
	CreepSquad* squad;

	Player* p;

	AttackStrategy* strategy;

	//functions
	//----------------------------------------

	void shootAvailableCreeps();

};
#endif