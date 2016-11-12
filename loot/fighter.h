#pragma once
#include <stdint.h>
#include "enemytype.h"
#include "player.h"

class Fighter
{
private:
	EnemyType type;
	int16_t hp,hpmax;
	int16_t attack,defence;

	char name[10];

	int8_t xoffset, yoffset;
public:
	void load(const EnemyType type);
	void player(const Player playerdata);

	void damage(const uint8_t attackpower)

	void die(void);
	void diehard(void);
};