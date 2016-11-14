#include <string.h>
#include "fighter.h"
#include "types.h"
#include "player.h"

void resetAll(int16_t hpmax,int16_t attack,int16_t defence,EnemyType type)
{
	this->hpmax = hpmax;
	this->hp = hpmax;
	this->attack = attack;
	this->defence = defence;
	this->type = type;
}

void Fighter::damage(const int16_t attackpower)
{
	hp -= attackpower;	//Do something defency with this
	if (hp < -hpmax/4)	//If severely damaged, explode!
	{
		diehard();
	}
	if (hp < 0)
	{
		die();
	}
};

void Fighter::die()
{

}
void Fighter::diehard()
{

}