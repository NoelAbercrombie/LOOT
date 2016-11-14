#include "battle.h"
#include "button.h"
#include "types.h"
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
		}; break;
		case battleMode::EnemyTurn:
		{
			enemyTurn();
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
}
void Battle::lose()
{
	end();
}
void Battle::end()
{
	//cleans stuff up to begin again later
	battleState = battleMode::Load;
}
void Battle::playerTurn(void)	{};
void Battle::enemyTurn(void)	{};

void Battle::drawWorld(void)	{};
void Battle::drawHUD(void)		{};

void Battle::drawMenu(void)		
{
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