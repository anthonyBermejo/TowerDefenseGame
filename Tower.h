#ifndef TOWER_H
#define TOWER_H

#include<SFML/Graphics.hpp>


class Map;
class Creep;

class Tower{

public:
	/*
	Ice Tower slows down creeps
	Cannon causes AoE damage
	Regular is boring
	Super is a combination of Cannon and Ice
	*/
	enum TOWER_TYPE{ ICE, CANNON, REGULAR, SUPER };

	Tower(TOWER_TYPE type, int level, sf::Vector2i mapPos, Map* map);
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
	double getCooldownTime() const;
	int getUpgradeCost() const;
	sf::Sprite getSprite() const;

	//setters
	//----------------------------------------
	void setUpgradeLevel(int level);

	//other functions
	//----------------------------------------
	void Update(double elapsedTime); //elapsedTime being the time passed since last update


private:
	//members
	//----------------------------------------
	int cost;
	int refund;
	int range;
	int baseDamage;
	int upgradeLevel;
	const TOWER_TYPE type;

	double cooldownTime;
	double cooldownElapsed;
	bool coolingDown;

	const sf::Vector2i mapPosition;
	
	sf::Sprite sprite;

	Map* map;

	//functions
	//----------------------------------------

	void shootAvailableCreeps(Map*);

};
#endif