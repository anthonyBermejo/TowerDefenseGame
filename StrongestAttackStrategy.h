#pragma once
#include "AttackStrategy.h"

class StrongestAttackStrategy : public AttackStrategy{
public:
	vector<DrawableCreep*> selectAttackTargets(Tower* t, CreepSquad* squad);

	string getStrategyName();
};