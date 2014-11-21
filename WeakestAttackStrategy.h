#pragma once
#include "AttackStrategy.h"
class WeakestAttackStrategy : public AttackStrategy{
	vector<Creep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};