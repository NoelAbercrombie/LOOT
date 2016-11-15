#include "battle.h"
#include "button.h"
#include "types.h"
#include "cutscenes.h"
#include "graphics.h"
#include "fighter.h"
#include "gamestate.h"
#include "system.h"

Battle::Battle(System & ab)
{
	this->ab = &ab;
}

void Battle::run()
{
	//this needs more stuff in it
	ab->setState(GameState::Gameplay);
}

void Battle::step(void)
{
	switch(battleState)	//ToDo : Pointerify this
	{
		case battleMode::Start:
		{
			start();
		}; break;
		case battleMode::Select:
		{	
			select();
		}; break;
		case battleMode::PlayerTurn:
		{
			playerTurn();
			if(enemy.alive())	{	battleState = battleMode::EnemyTurn;	}
			else	{	battleState = battleMode::win;	}
		}; break;
		case battleMode::EnemyTurn:
		{
			enemyTurn();
			if(player.alive())	{	battleState = battleMode::Select;	}
			else	{	battleState = battleMode::Lose;	}
		}; break;
		case battleMode::Win:
		{
			win();
		}; break;
		case battleMode::Lose:
		{
			lose();
		}; break;
	};
}

void Battle::load()
{
	//hardcoding a skellybones in here, change later
	enemy.resetAll(100,25,30,EnemyType::Skellybones);
	enemy.drawy = -64;

	//player stats are retained from last battle?
	battleState = battleMode::Start;
}

void Battle::start()
{
	enemy.drawy += 2;
	if (enemy.drawy >= enemy.yoffset)
	{
		enemy.drawy = enemy.yoffset;
		battleState = battleMode::Select;	//go to battle menu
	}
}

void Battle::win()
{
	end();
	ab->setState(GameState::Gameplay);
}
void Battle::lose()
{
	end();
	cutscenes->start(CutsceneType::Gameover,GameState::Menu);
}
void Battle::end()
{
	//cleans stuff up to begin again later
	battleState = battleMode::Load;
}
void Battle::playerTurn(void)	
{
	//tie into attack picker later
	enemy.damage(player.attack);
};
void Battle::enemyTurn(void)	
{
	//insert AI here
};

void Battle::drawWorld(void)	{};
void Battle::drawHUD(void)		{};

void Battle::drawMenu(void)		
{
	//hold my beer, i've got this
	const char PROGMEM text00 = "BATTLE!";const char PROGMEM text01 = "FIGHT";const char PROGMEM text02 = "ITEM";const char PROGMEM text03 = "RUN";
	const char PROGMEM text10 = "FIGHT!"; const char PROGMEM text11 = "ATTACK";const char PROGMEM text12="BACK";
	const char PROGMEM text20 = "ITEMS\n";	//rest is generated
	const char PROGMEM text30 = "RUN!"; const char PROGMEM text31="No";	const char PROGMEM text32="Yes";

	const char* const PROGMEM texttable[] = { text00,text01,text02,text03,text10,text11,text12,text20,text30,text31,text32 };
	const uint8_t const PROGMEM textnum[] = { 4,3,1,3 };
	const uint8_t const PROGMEM textoffset[] = { 0,4,7,8 };

	uint8_t menuID = <uint8_t>menu;	//cast out ID of menu page
	uint8_t count = pgm_read_byte(textnum+menuID);	//get number of items on page
	uint8_t offset = pgm_read_byte(textoffset+menuID);	//text array offset
	char buffer[8];	//text buffer
	for(uint8_t i=0; i<count; ++i)
	{
		strcpy_p(buffer, (PGM_P)pgm_read_word(&(string_table[offset+i])));	//wat
		ab->setCursor(66,2+(i*8));
		ab->print(buffer);
	}

	if(menu==battleMenu::Item)
	{
		//draw item selector here
	}
};

void Battle::select(void)
{
	if(ab->isPushed(Button::Up))
		{	menuSelect--;	}
	if(ab->isPushed(Button::Down))
		{	menuSelect++;	}
	if(menuSelect<0)	{	menuSelect = 0;	}

	switch(menu)
	{
		case 0://battleMenu::Top:
		{

		};	break;
		case 1://battleMenu::Fight:
		{	

		};	break;
		case 2://battleMenu::Item:
		{

		};	break;
		case 3://battleMenu::Run:
		{

		}; 	break;
	}
}

void Battle::draw(void)
{
	drawWorld();
	drawHUD();
	if (battleState == battleMode::Select)
	{
		drawMenu();
	}
	else
	{
		/*
		What to put here? Some sort of update feed?
		>Skellybones attacks!
		>Critical hit 104HP!
		>YOU DIED
		etc
		*/
	}
}