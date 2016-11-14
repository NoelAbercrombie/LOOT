#include "battle.h"
#include "types.h"
#include "graphics.h"
#include "fighter.h"
#include "gamestate.h"
#include "system.h"

Battle::Battle(System & ab)
{
	this->ab = &ab;
}

void Battle::start(void)
{
	enemyAnim = -32;
	enemyStop = System::ScreenCentreY + 8;

	battleState = battleType::Start;
	//enemy.load(EnemyType Skeleton);
	//player.Player(Player playerData);
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

	enemy.xoffset = 48;
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
void Battle::drawMenu(void)		{};

void Battle::select(void)
{
	//stubbity stub
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