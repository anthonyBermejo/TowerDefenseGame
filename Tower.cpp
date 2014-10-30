/*#include "Tower.h"
#include <iostream>
#include "Creep.h"
#include "Map.h"

using namespace std;

Tower::Tower(Tower::TOWER_TYPE type, int level, int xpos, int ypos, Map* map) : type(type), upgradeLevel(level), xpos(xpos), ypos(ypos), map(map) {

	coolingDown = false;
	cooldownElapsed = 0;

	//initialize variables based on the tower type
	switch (type){
	case TOWER_TYPE::REGULAR:
		cost = 100;
		refund = 80;
		range = 6;
		baseDamage = 5;

		cooldownTime = 1;

		break;

	case TOWER_TYPE::ICE:
		cost = 150;
		refund = 130;
		range = 4;
		baseDamage = 4;

		cooldownTime = 1.3;

		break;

	case TOWER_TYPE::CANNON:
		cost = 200;
		refund = 180;
		range = 5;
		baseDamage = 10;

		cooldownTime = 2.5;

		break;

	case TOWER_TYPE::SUPER:
		cost = 500;
		refund = 400;
		range = 7;
		baseDamage = 12;

		cooldownTime = 1.5;

		break;
	}
}

Tower::~Tower(){
	//get rid of map pointer
	map = NULL;
}

//getters
//----------------------------------------------
int Tower::getCost() const{ return cost; }
int Tower::getRefund() const{ return refund; }
int Tower::getRange() const{ return range; }
int Tower::getDamage() const{
	//damage is calculated by having the base damage and adding
	//increments of 20% depending on it's upgrade level
	//ie, at upgrade level 2 a tower gets an additional 40% of
	//the base damage added

	return baseDamage + (int)(baseDamage * (upgradeLevel*0.2));
}
int Tower::getUpgradeLevel() const{ return upgradeLevel; }
bool Tower::isCoolingDown() const{ return coolingDown; }
int* Tower::getPosition() const{
	int* position = new int[2];
	position[0] = xpos;
	position[1] = ypos;
	return position;
}
double Tower::getCooldownTime() const{ return cooldownTime; }

int Tower::getUpgradeCost() const{
	//for now, upgrade cost is calculated by taking the base cost
	//of the tower, multiplying it by the level higher than itself
	//then dividing that value by two
	//This will probably be adjusted later for balancing

	return (cost * (upgradeLevel + 1)) / 2;
}

Tower::TOWER_TYPE Tower::getType() const{ return type; }

//setters
//----------------------------------------------
void Tower::setUpgradeLevel(int upgradeLevel){ this->upgradeLevel = upgradeLevel; }

//Juicy stuff
//----------------------------------------------
void Tower::Update(double elapsedTime){
	//initially, check to see if tower is cooling down
	if (coolingDown){
		cooldownElapsed += elapsedTime;


		//go back to kicking ass once cool down is over
		if (cooldownElapsed >= cooldownTime){
			coolingDown = false;
			cooldownElapsed = 0;
			cout << "\nTower Reloaded" << endl;
		}
	}
	else{//ready to shoot
		shootAvailableCreeps(map);
	}
}

void Tower::shootAvailableCreeps(Map* m){
	int numInRange = m->getNumCreepsInRange(this);

	//creeps were found
	if (numInRange > 0){
		cout << "\nTower shoots!\n";

		//get the creeps that are in range of this tower
		//multiple creeps are returned only when the tower
		//does AoE damage
		Creep** creeps = m->getCreepsInRange(this);

		//damage all creeps that apply
		for (int i = 0; i < numInRange; ++i)
			creeps[i]->damage(this);

		coolingDown = true;

		//get rid of creep pointers
		for (int i = 0; i < numInRange; i++)
			creeps[i] = NULL; // Don't delete the creep objects because they are still pointed to in Map

		delete[] creeps;
		creeps = NULL;
	}

}*/