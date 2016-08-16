#pragma once
#include <stdint.h>
#include "system.h"
#include "enemytype.h"
//#include "fighter.h"

class Fighter;

class Battle
{
private:
	System * ab;
	//Fighter player;
	//Fighter enemy;
	bool ready;

	//menu
	uint8_t battleMenu;
	uint8_t battleSelect; 

	//animation
	int8_t enemyAnim;
	int8_t enemyStop;

public:
	Battle(System & ab);

	void start(void);
	void step(void);
	void draw(void);

	//drawing helpers
	void drawBar(const uint8_t x, const uint8_t y, const uint8_t length, const uint8_t percent);
};
