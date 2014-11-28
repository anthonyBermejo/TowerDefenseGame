#pragma once
#include "AttackStrategy.h"
class WeakestAttackStrategy : public AttackStrategy{
public:
	vector<DrawableCreep*> selectAttackTargets(Tower* t, CreepSquad* squad);

	string getStrategyName();
};