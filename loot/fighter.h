#pragma once
#include <stdint.h>
#include <Arduino.h>
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

	void resetAll(int16_t hpmax,int16_t attack,int16_t defence,EnemyType type);

	void damage(const int16_t attackpower);

	void die(void);
	void diehard(void);

	int8_t getXoffset(void)	{	return this->xoffset;	}
	int8_t getYoffset(void)	{	return this->yoffset;	}

	bool alive(void)	{	return this->hp>0;	}
	int16_t getHP(void)	{	return this->hp;	}
	int16_t getHPMax(void)	{	return this->hpmax;	}
	int16_t getAttack(void)	{	return this->attack;	}
	int16_t getDefence(void){	return this->defence;	}
	//int8_t getHPPercent(void)	{	return min(max((this->hp/this->hpmax)*100,0),100);	}	//Does this work?
};