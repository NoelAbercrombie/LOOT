#pragma once
#include <stdint.h>
#include "system.h"
#include "battlemode.h"
#include "enemytype.h"
#include "player.h"

class Fighter;

class Battle
{
private:
	System * ab;
	Player * playerData;

	//Fighter player;
	//Fighter enemy;
	bool ready;

	//menu
	uint8_t menu;
	uint8_t select; 

	//animation
	int8_t enemyAnim;
	int8_t enemyStop;

	battleMode battleState;	//to:do make this a type
public:
	Battle(System & ab, Player & playerData);

	void begin();
	void step();
	void draw();

	//battle states, needs a tidy. 
	void start(void);		
	void menu(void);		void menuDraw(void);
	void playerTurn(void);	void playerTurnDraw(void);
	void enemyTurn(void);	void enemyTurnDraw(void);
	void win(void);			void winDraw(void);
	void lose(void);		void loseDraw(void);
	
	//drawing helpers
	void drawBar(const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t value, const uint8_t capacity);
};
