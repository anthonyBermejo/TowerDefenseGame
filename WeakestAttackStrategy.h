#pragma once
#include "AttackStrategy.h"
class WeakestAttackStrategy : public AttackStrategy{
	vector<DrawableCreep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};