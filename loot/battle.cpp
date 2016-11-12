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
	switch(battleState)
	{
		case battleType::PlayerTurn
		{
			enemy.damage(player.attackpower);
		}; break;
		case battleType::EnemyTurn
		{
			player.damage(enemy.attackpower);
		}; break;
	}
}

void Battle::draw(void)
{
	ab->drawSpriteCentred(System::ScreenCentreX / 2, enemyAnim, imgSkeleton1, 1);

	if (enemyAnim < enemyStop)
	{
		ab->setCursor(System::ScreenCentreX+2, 8);
		ab->print(F("Skellybones wants"));
		ab->setCursor(System::ScreenCentreX+2, 16);
		ab->print(F("to fight!"));
	}
	else
	{
		//draw hp bars
		drawBar(2, 2 , System::ScreenCentreX-4, 40, 60);
		drawBar(System::ScreenCentreX+2, 2, System::ScreenCentreX-4, 100, 110);

		if (battleState == battleType::Select)
		{
	      ab->setCursor(System::ScreenCentreX+10, 16);
	      ab->print(F("Fight"));
	      ab->setCursor(System::ScreenCentreX+10, 24);
	      ab->print(F("Item"));
	      ab->setCursor(System::ScreenCentreX+10, 32);
	      ab->print(F("Run"));
	      //select cursor
	      ab->setCursor(System::ScreenCentreX+2, 16 + (8 * select));
	      ab->print(F(">"));
		}
	}
}

