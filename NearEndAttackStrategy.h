#pragma once
#include "AttackStrategy.h"
class NearEndAttackStrategy: public AttackStrategy{
public:
	vector<DrawableCreep*> selectAttackTargets(Tower* t, CreepSquad* squad);

	string getStrategyName();
};