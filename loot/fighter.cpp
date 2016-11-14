#include <string.h>
#include "fighter.h"
#include "types.h"
#include "player.h"

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