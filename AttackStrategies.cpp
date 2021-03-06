#include "NearestAttackStrategy.h"
#include "NearEndAttackStrategy.h"
#include "WeakestAttackStrategy.h"
#include "StrongestAttackStrategy.h"
#include "Tower.h"

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------
//Attack Strategy for selecting nearest target
//------------------------------------------------------------------------------------------------------------------------------------
vector<DrawableCreep*> NearestAttackStrategy::selectAttackTargets(Tower* t, CreepSquad* squad){
	//get creeps
	vector<DrawableCreep*> creeps = squad->getCreeps();

	DrawableCreep* closestCreep = NULL;
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
	
	vector<DrawableCreep*> creepsToTarget;

	//if no creeps have been found, return an empty vector
	if (closestCreep == NULL)
		return creepsToTarget;

	//there are creeps, so push onto the vector
	creepsToTarget.push_back(closestCreep);


	//search for creeps within range if AoE damage
	if (t->getType() == Tower::CANNON || t->getType() == Tower::SUPER){
		
		int xOrigin = closestCreep->getLocationX();
		int yOrigin = closestCreep->getLocationY();

		//search for creeps within 2 blocks around the closestCreep
		for (int i = 0; i < creeps.size(); ++i){
			if (abs(xOrigin - creeps[i]->getLocationX()) <= 2 &&
				abs(yOrigin - creeps[i]->getLocationY()) <= 2 &&
				closestCreep != creeps[i]){
				creepsToTarget.push_back(creeps[i]);
			}
		}
	}

	return creepsToTarget;
}

string NearestAttackStrategy::getStrategyName(){
	return "Nearest";
}

//------------------------------------------------------------------------------------------------------------------------------------
//Attack strategy for selecting creep nearest to the end tile
//------------------------------------------------------------------------------------------------------------------------------------
vector<DrawableCreep*> NearEndAttackStrategy::selectAttackTargets(Tower* t, CreepSquad* squad){
	//get creeps
	vector<DrawableCreep*> creeps = squad->getCreeps();

	DrawableCreep* closestCreep = NULL;
	int closestDistance = 0;
	int currentDistance = 0;

	//loop through all the creeps and find the closest to the endTile
	for (int i = 0; i < creeps.size(); ++i){
		//check if creep is within range
		if (creeps[i]->getHitPoints() > 0 && abs(t->getMapPosition().x - creeps[i]->getLocationX()) <= t->getRange() &&
			abs(t->getMapPosition().y - creeps[i]->getLocationY()) <= t->getRange()){

			//calculate distance to end point
			currentDistance = (abs(t->getEndPointPosition().x - creeps[i]->getLocationX())) + (abs(t->getEndPointPosition().y - creeps[i]->getLocationY()));

			//check if the current creep is closer than the previously determined one
			//if closestCreep is NULL, then this is first iteration
			if (closestCreep == NULL || currentDistance < closestDistance){
				closestCreep = creeps[i];
				closestDistance = currentDistance;
			}

		}
	}

	vector<DrawableCreep*> creepsToTarget;

	//if no creeps have been found in range, return empty vector
	if (closestCreep == NULL)
		return creepsToTarget;

	//creep has been found that's in range
	creepsToTarget.push_back(closestCreep);

	//search for creeps within range if AoE damage
	if (t->getType() == Tower::CANNON || t->getType() == Tower::SUPER){

		int xOrigin = closestCreep->getLocationX();
		int yOrigin = closestCreep->getLocationY();

		//search for creeps within 2 blocks around the closestCreep
		for (int i = 0; i < creeps.size(); ++i){
			if (abs(xOrigin - creeps[i]->getLocationX()) <= 2 &&
				abs(yOrigin - creeps[i]->getLocationY()) <= 2 &&
				closestCreep != creeps[i]){
				creepsToTarget.push_back(creeps[i]);
			}
		}
	}

	return creepsToTarget;

}

string NearEndAttackStrategy::getStrategyName(){
	return "Nearest End";
}


//------------------------------------------------------------------------------------------------------------------------------------
//Attack strategy for selecting the weakest creep
//------------------------------------------------------------------------------------------------------------------------------------
vector<DrawableCreep*> WeakestAttackStrategy::selectAttackTargets(Tower* t, CreepSquad* squad){
	//get creeps
	vector<DrawableCreep*> creeps = squad->getCreeps();

	DrawableCreep* weakestCreep = NULL;

	//loop through creeps looking for the weakest
	for (int i = 0; i < creeps.size(); ++i){
		//check if creep is within range of the tower
		if (creeps[i]->getHitPoints() > 0 && abs(t->getMapPosition().x - creeps[i]->getLocationX()) <= t->getRange() &&
			abs(t->getMapPosition().y - creeps[i]->getLocationY()) <= t->getRange()){
		
			//check if current creep is the weakest
			//if weakestCreep is NULL, then it is the first iteration through the creeps
			if (weakestCreep == NULL || weakestCreep->getHitPoints() > creeps[i]->getHitPoints())
				weakestCreep = creeps[i];
		}
	}

	vector<DrawableCreep*> creepsToTarget;

	//if weakestCreep is NULL, then no creeps are in range
	//return empty vector
	if (weakestCreep == NULL)
		return creepsToTarget;

	//add the weakest to the vector
	creepsToTarget.push_back(weakestCreep);

	//search for creeps within range if AoE damage
	if (t->getType() == Tower::CANNON || t->getType() == Tower::SUPER){

		int xOrigin = weakestCreep->getLocationX();
		int yOrigin = weakestCreep->getLocationY();

		//search for creeps within 2 blocks around the closestCreep
		for (int i = 0; i < creeps.size(); ++i){
			if (abs(xOrigin - creeps[i]->getLocationX()) <= 2 &&
				abs(yOrigin - creeps[i]->getLocationY()) <= 2 &&
				weakestCreep != creeps[i]){
				creepsToTarget.push_back(creeps[i]);
			}
		}
	}

	return creepsToTarget;

}

string WeakestAttackStrategy::getStrategyName(){
	return "Weakest";
}

//------------------------------------------------------------------------------------------------------------------------------------
//Attack strategy for selecting the strongest creep
//------------------------------------------------------------------------------------------------------------------------------------
vector<DrawableCreep*> StrongestAttackStrategy::selectAttackTargets(Tower* t, CreepSquad* squad){
	//get creeps
	vector<DrawableCreep*> creeps = squad->getCreeps();

	DrawableCreep* strongestCreep = NULL;

	//loop through creeps looking for the strongest
	for (int i = 0; i < creeps.size(); ++i){
		//check if creep is within range of tower
		if (creeps[i]->getHitPoints() > 0 && abs(t->getMapPosition().x - creeps[i]->getLocationX()) <= t->getRange() &&
			abs(t->getMapPosition().y - creeps[i]->getLocationY()) <= t->getRange()){
			
			//check if current creep is the strongest
			//if strongestCreep is NULL then this is the first iteration through creeps
			if (strongestCreep == NULL || strongestCreep->getHitPoints() < creeps[i]->getHitPoints())
				strongestCreep = creeps[i];
		}
	}

	vector<DrawableCreep*> creepsToTarget;

	//return empty vector is no creep was found in range
	if (strongestCreep == NULL)
		return creepsToTarget;

	//add the strongest creep to vector
	creepsToTarget.push_back(strongestCreep);

	//search for creeps within range if AoE damage
	if (t->getType() == Tower::CANNON || t->getType() == Tower::SUPER){

		int xOrigin = strongestCreep->getLocationX();
		int yOrigin = strongestCreep->getLocationY();

		//search for creeps within 2 blocks around the closestCreep
		for (int i = 0; i < creeps.size(); ++i){
			if (abs(xOrigin - creeps[i]->getLocationX()) <= 2 &&
				abs(yOrigin - creeps[i]->getLocationY()) <= 2 &&
				strongestCreep != creeps[i]){
				creepsToTarget.push_back(creeps[i]);
			}
		}
	}

	return creepsToTarget;

}

string StrongestAttackStrategy::getStrategyName(){
	return "Strongest";
}
