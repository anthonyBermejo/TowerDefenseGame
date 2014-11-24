#pragma once
#include "AttackStrategy.h"

class StrongestAttackStrategy : public AttackStrategy{
	vector<DrawableCreep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};