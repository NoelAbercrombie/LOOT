#pragma once
#include <stdint.h>
#include "enemytype.h"
#include "player.h"

class Fighter
{
private:
	EnemyType type;
	int8_t hp;
	int8_t hpMax;
	char name[10];

	int8_t xoffset, yoffset;
public:
	void load(const EnemyType type);
	void player(const Player playerdata);
};