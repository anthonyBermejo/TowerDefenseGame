#include "Tower.h"
#include <iostream>

using namespace std;

Tower::Tower(TOWER_TYPE type, int level, sf::Vector2i mapPos, CreepSquad* creepSquad,Player* p,TextureManager* tm) : type(type), upgradeLevel(level), mapPosition(mapPos), squad(creepSquad), p(p), tm(tm) {

	coolingDown = false;
	cooldownElapsed = sf::Time::Zero;

	sprite.setTexture(tm->getTexture(TextureManager::TEXTURE::TOWER));
	sprite.setPosition(sf::Vector2f(mapPosition.x * 24.0f, mapPosition.y * 24.0f));

	//initialize variables based on the tower type
	switch (type){
	case TOWER_TYPE::REGULAR:
		cost = 100;
		refund = 80;
		range = 6;
		baseDamage = 5;

		cooldownTime = sf::milliseconds(1000);

		sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));

		break;

	case TOWER_TYPE::ICE:
		cost = 150;
		refund = 130;
		range = 4;
		baseDamage = 4;

		cooldownTime = sf::milliseconds(1300);

		sprite.setTextureRect(sf::IntRect(24, 0, 24, 24));

		break;

	case TOWER_TYPE::CANNON:
		cost = 200;
		refund = 180;
		range = 5;
		baseDamage = 10;

		cooldownTime = sf::milliseconds(2500);

		sprite.setTextureRect(sf::IntRect(48, 0, 24, 24));

		break;

	case TOWER_TYPE::SUPER:
		cost = 500;
		refund = 400;
		range = 7;
		baseDamage = 12;

		cooldownTime = sf::milliseconds(1500);

		sprite.setTextureRect(sf::IntRect(72, 0, 24, 24));

		break;
	}
}

Tower::~Tower(){
	//get rid of map pointer
	squad = NULL;
	p = NULL;
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
sf::Vector2i Tower::getMapPosition() const{ return mapPosition; }
sf::Time Tower::getCooldownTime() const{ return cooldownTime; }

int Tower::getUpgradeCost() const{
	//for now, upgrade cost is calculated by taking the base cost
	//of the tower, multiplying it by the level higher than itself
	//then dividing that value by two
	//This will probably be adjusted later for balancing

	return (cost * (upgradeLevel + 1)) / 2;
}

Tower::TOWER_TYPE Tower::getType() const{ return type; }


int Tower::getTowerTypeCost(TOWER_TYPE t){
	switch (t){
	case REGULAR:
		return 100;
	case ICE:
		return 150;
	case CANNON:
		return 200;
	case SUPER:
		return 500;
	}
}

//setters
//----------------------------------------------
void Tower::setUpgradeLevel(int upgradeLevel){ this->upgradeLevel = upgradeLevel; }

//Juicy stuff
//----------------------------------------------
void Tower::Update(sf::Time elapsedTime){
	//initially, check to see if tower is cooling down
	if (coolingDown){
		cooldownElapsed += elapsedTime;


		//go back to kicking ass once cool down is over
		if (cooldownElapsed >= cooldownTime){
			coolingDown = false;
			cooldownElapsed = sf::Time::Zero;
			cout << "\nTower Reloaded" << endl;
		}
	}
	else{//ready to shoot
		shootAvailableCreeps();
		coolingDown = true;
	}
}

void Tower::Draw(sf::RenderWindow* w){
	w->draw(sprite);
}

void Tower::shootAvailableCreeps(){
	vector<Creep*> creeps = squad->getCreeps();

	//loop through creeps and find closest creep, then damage it and pop out
	//
	//IN THE FUTURE -> no check for finding the CLOSEST, at the moment only the first encountered in the vector that is in range
	for (int i = 0; i < creeps.size(); ++i){
		if (abs(mapPosition.x - creeps[i]->getLocationX()) <= range &&
			abs(mapPosition.y - creeps[i]->getLocationY()) <= range){
			//AOE damage - for now, all AOE has 3 block radius 
			if (type == TOWER_TYPE::CANNON || type == TOWER_TYPE::SUPER){
				int xOrigin = creeps[i]->getLocationX();
				int yOrigin = creeps[i]->getLocationY();
				for (int j = 0; i < creeps.size(); ++i){
					if (abs(xOrigin - creeps[j]->getLocationX()) <= 2 &&
						abs(yOrigin - creeps[j]->getLocationY()) <= 2){
						if (creeps[j]->getHitPoints() > 0){
							creeps[j]->damageCreep(p, getDamage());
							cout << "Fired!\n";
						}
					}
				}
				break;
			}
			
			if (creeps[i]->getHitPoints() > 0){
				creeps[i]->damageCreep(p, getDamage());
				cout << "Fired!\n";
				break;
			}
		}
	}

	//set cooling down
	coolingDown = true;
}