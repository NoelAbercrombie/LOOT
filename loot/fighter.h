#pragma once
#include <stdint.h>
#include "enemytype.h"

class Fighter
{
private:
	int8_t hp;

	EnemyType type;
	uint8_t * sprite;
public:
	Fighter(const EnemyType,const int8_t hp);
	int8_t getHP();
	void setHP(const int8_t hp);
	void setSprite(const uint8_t * sprite);
};