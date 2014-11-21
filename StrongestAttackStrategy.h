#pragma once
#include "AttackStrategy.h"

class StrongestAttackStrategy : public AttackStrategy{
	vector<Creep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};