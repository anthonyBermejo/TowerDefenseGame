#pragma once
#include "CreepSquad.h"

class Tower;

class AttackStrategy{
public:
	virtual vector<DrawableCreep*> selectAttackTargets(Tower* t, CreepSquad* squad) = 0;

	virtual string getStrategyName() = 0;
};