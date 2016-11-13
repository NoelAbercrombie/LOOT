#include "battle.h"
#include "enemytype.h"
#include "battlemode.h"
#include "graphics.h"
#include "fighter.h"
#include "gamestate.h"
#include "system.h"

Battle::Battle(System & ab, Player & playerData)
{
	this->ab = &ab;
	this->playerData = &playerData;
}

Battle::Step(void)
{
	switch(battleState)	//ToDo : Pointerify this
	{
		case BattleMode::start:
		{
			start();
		}; break;
		case BattleMode::Menu:
		{
			menu();
		}; break;
		case BattleMode::playerTurn
		{
			playerTurn();
		}; break;
		case BattleMode::enemyTurn
		{
			enemyTurn();
		}; break;
		case BattleMode::win
		{
			win();
		}; break;
		case BattleMode::lose
		{
			lose();
		}; break;
	}
}

void Battle::draw(void)
{
	switch(battleState)	//ToDo : Pointerify this
	{
		case BattleMode::start:
		{
			startDraw();
		}; break;
		case BattleMode::Menu:
		{
			menuDraw();
		}; break;
		case BattleMode::playerTurn
		{
			playerTurnDraw();
		}; break;
		case BattleMode::enemyTurn
		{
			enemyTurnDraw();
		}; break;
		case BattleMode::win
		{
			winDraw();
		}; break;
		case BattleMode::lose
		{
			loseDraw();
		}; break;
	}
}