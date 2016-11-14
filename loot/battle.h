#pragma once
#include <stdint.h>
#include "system.h"
#include "types.h"
#include "player.h"
#include "fighter.h"

class Battle
{
private:
	System * ab;
	Player * playerData;

	//Fighter player;
	//Fighter enemy;
	bool ready;

	//menu
	int8_t menu;
	int8_t menuselect; 

	//animation
	int8_t enemyAnim;
	int8_t enemyStop;

	Fighter player;
	Fighter enemy;

	battleMode battleState;
public:
	Battle(System & ab);

	void step(void);
	void draw(void);

	//UI chunks
	void drawWorld(void);
	void drawHUD(void);
	void drawMenu();

	//battle states, needs pointerification
	void load(void);
	void start(void);		
	void select(void);		
	void playerTurn(void);	
	void enemyTurn(void);	
	void run(void);
	void win(void);			
	void lose(void);		

	void end(void);
	
	//drawing helpers
	void drawBar(const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t value, const uint8_t capacity);
};
