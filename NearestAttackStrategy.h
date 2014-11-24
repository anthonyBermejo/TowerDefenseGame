#pragma once
#include "AttackStrategy.h"
class NearestAttackStrategy : public AttackStrategy{
public:
	vector<DrawableCreep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};