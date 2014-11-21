#pragma once
#include "AttackStrategy.h"
class NearEndAttackStrategy: public AttackStrategy{
	vector<Creep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};