#include "NearestAttackStrategy.h"

using namespace std;

vector<Creep*> NearestAttackStrategy::selectAttackTargets(Tower* t, CreepSquad* squad){
	//get creeps
	vector<DrawableCreep*> creeps = squad->getCreeps();

	Creep* closestCreep = NULL;
	int closestDistance=0;
	int currentDistance=0;

	//loop through all creeps in the squad and get the nearest creep
	for (int i = 0; i < creeps.size(); ++i){
		
		//check if creep is within range of the tower
		if (creeps[i]->getHitPoints() > 0 && abs(t->getMapPosition().x - creeps[i]->getLocationX()) <= t->getRange() &&
			abs(t->getMapPosition().y - creeps[i]->getLocationY()) <= t->getRange()){

			//calculate distace
			currentDistance = (abs(t->getMapPosition().x - creeps[i]->getLocationX())) + (abs(t->getMapPosition().y - creeps[i]->getLocationY()));

			//current creep is closer than the previously found one
			//checks if NULL, which in that situation means it's the first creep in the squad
			if (closestCreep == NULL || currentDistance < closestDistance){
				closestCreep = creeps[i];
				closestDistance = currentDistance;
			}
		}
	}

	//Should have the closest creep now

	
	vector<Creep*> creepsToTarget;
	creepsToTarget.push_back(closestCreep);


	//search for creeps within range if AoE damage
	if (t->getType() == Tower::CANNON || t->getType() == Tower::SUPER){
		
		int xOrigin = closestCreep->getLocationX();
		int yOrigin = closestCreep->getLocationY();

		//search for creeps within 2 blocks around the closestCreep
		for (int i = 0; i < creeps.size(); ++i){
			if (abs(xOrigin - creeps[i]->getLocationX()) <= 2 &&
				abs(yOrigin - creeps[i]->getLocationY()) <= 2){
				creepsToTarget.push_back(creeps[i]);
			}
		}
	}

	return creepsToTarget;
}