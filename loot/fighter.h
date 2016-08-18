#pragma once
#include <stdint.h>
#include "enemytype.h"
#include "player.h"

class Fighter
{
private:
	int8_t hp;
	int8_t hpMax;
	char name[8];
public:
	void load(const EnemyType type);
	void player(Player playerdata);
};