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

	int8_t xoffset, yoffset;	//Store with sprite data?
public:
	int8_t drawy;

	void resetAll(int16_t hpmax,int16_t attack,int16_t defence,EnemyType type)

	void damage(const int16_t attackpower);

	void die(void);
	void diehard(void);

	int16_t getHP(void)	{	return this->hp;	}
	int16_t getHPMax(void)	{	return this->hpmax;	}
	int8_t getHPPercent(void)	{	return clamp((this->hp/this->hpmax)*100,0,100);	}	//Does this work?
};