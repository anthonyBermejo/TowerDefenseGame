#pragma once
#include "Tower.h"
#include "CreepSquad.h"
class AttackStrategy{
public:
	virtual vector<Creep*> selectAttackTargets(Tower* t, CreepSquad* squad);
};