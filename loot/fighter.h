#pragma once
#include <stdint.h>
#include "types.h"

class Fighter
{
private:
	//sort out private-ing this later
	EnemyType type;
	int16_t hp,hpmax;
	int16_t attack,defence;

public:
	int8_t xoffset, yoffset;
	int8_t drawy;

	void resetAll(int16_t hpmax,int16_t attack,int16_t defence,EnemyType type)
	{
		this->hpmax = hpmax;
		this->hp = hpmax;
		this->attack = attack;
		this->defence = defence;
		this->type = type;
	}

	void damage(const int16_t attackpower);

	void die(void);
	void diehard(void);
};