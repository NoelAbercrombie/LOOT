#pragma once
#include <stdint.h>
#include "enemytype.h"
#include "player.h"

class Fighter
{
private:
	int8_t hp;
	int8_t hpMax;
	char name[10];
public:
	void load(const EnemyType type);
	void player(const Player playerdata);
};