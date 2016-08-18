#include "fighter.h"
#include "enemytype.h"
#include "player.h"

void Fighter::load(const EnemyType type);
{
	//To:do : Load character data from progmem.
	name = "Skeleton";
	hpMax = 30;
	hp = hpMax;

}

void Fighter::Player(Player playerdata)	//Uses players stats
{
	hpMax = playerdata.hpMax;
	hp = playerdata.hp;
}

void Fighter::setHP(const int8_t hp)
{
	this->hp = hp;
}

int8_t Fighter::getHP()
{
	return this->hp;
}