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

void Battle::start(void)
{
	enemyAnim = -32;
	enemyStop = System::ScreenCentreY + 8;

	battleState = 0;	//battleState = BattleType::Intro;
	//enemy.load(EnemyType Skeleton);
	//player.Player(Player playerData);
}

void Battle::attack()
{
	//?
}

void Battle::step(void)
{
	switch(battleState)
	{
		case 0:	//battle start
		{
			enemyAnim += 4;
			if(enemyAnim < enemyStop)
			{
				battleState = 1;	//battleState = battleType::Menu;
			}
		}; break;
		case 1:
		{
			if(ab->isPushed(Button::Up)
			{
				if(select > 0)	select--;
			}
			if(ab->isPushed(Button::Down))
			{
				if(select < 2)	select++;
			}
			if(ab->isPushed(Button::A))
			{
				switch(select)
				{
					case 0:
					{
						attack();
					}; break;
					case 1:
					{
						
					}; break;
					case 2:
					{
						run();
					}; break;
				}
			}
		}; break;
	}
}

void Battle::drawBar(const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t value, const uint8_t capacity)
{
	int8_t length = width;
	if (value > capacity)
	{
		length = (value / capacity) * width;
	}

	ab->fillRect(x, y, width, 5, 0);
	ab->drawRect(x, y, width, 5, 1);
	ab->drawLine(x, y+2, x+length, y+2, 1);
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

		if (ready)
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

