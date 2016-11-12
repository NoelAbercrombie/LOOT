#include <string.h>
#include "fighter.h"
#include "enemytype.h"
#include "player.h"

void Fighter::load(const EnemyType type)
{
	//To:do : Load character data from progmem.
	char tempname[] = "Skeleton";
	strcpy(name,tempname);
	hpMax = 30;
	hp = hpMax;

}

void Fighter::player(const Player playerdata)	//Uses players stats
{
	strcpy(name,"You");
	hpMax = playerdata.hpMax;
	hp = playerdata.hp;
}

void damage(const uint8_t attackpower)
{
	hp -= attackpower;	//Do something defency with this
	if (hp < -hpmax/4)	//If severely damaged, explode!
	{
		diehard()
	}
	if (hp < 0)
	{
		die();
	}
};