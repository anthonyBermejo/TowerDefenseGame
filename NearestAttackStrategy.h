#pragma once
#include "AttackStrategy.h"
class NearestAttackStrategy : public AttackStrategy{
public:
	vector<Creep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};