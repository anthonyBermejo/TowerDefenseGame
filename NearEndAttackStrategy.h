#pragma once
#include "AttackStrategy.h"
class NearEndAttackStrategy: public AttackStrategy{
	vector<DrawableCreep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};