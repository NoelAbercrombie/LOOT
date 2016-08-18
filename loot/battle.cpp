#include "battle.h"
#include "enemytype.h"
#include "graphics.h"
#include "fighter.h"
#include "gamestate.h"
#include "system.h"

Battle::Battle(System & ab, Player & playerData);
{
	this->ab = &ab;
	this->playerData = &playerData;
}

void Battle::start(void)
{
	enemyAnim = -32;
	enemyStop = System::ScreenCentreY + 8;

	enemy.load(EnemyType Skeleton);
	player.Player(Player playerData);
}


void Battle::step(void)
{
	ready = true;
	if(enemyAnim < enemyStop)
	{
		enemyAnim += 4;
		ready = false;
	}

	if(ready)	//if the player can press buttons
	{
		if(ab->isPressed(Button::A))
		{
			ab->setState(GameState::Gameplay);
		}
	}
}

void Battle::drawBar(const uint8_t x, const uint8_t y, const uint8_t length, const uint8_t percent)
{
	const uint8_t barWidth = length-2;

	ab->fillRect(x, y, barWidth, 6, 0);
	ab->drawRect(x+1, y+1, length, 4, 1);	

	const uint8_t value = min(length * (percent / 100), length); 
	ab->drawRect(x+1, y+1, value, 4, 1);	
}

void Battle::draw(void)
{
	ab->drawSpriteCentred(System::ScreenCentreX / 2, enemyAnim, imgSkeleton1, 1);

	//draw hp bars
	drawBar(1, 1, System::ScreenCentreX-2, 100);
	drawBar(System::ScreenCentreX+1, 1, System::ScreenCentreX-2, 100);

	ab->setCursor(System::ScreenCentreX+2, 16);
	ab->print(F(">Fight"));
	ab->setCursor(System::ScreenCentreX+2, 24);
	ab->print(F(" Item"));
	ab->setCursor(System::ScreenCentreX+2, 32);
	ab->print(F(" Run"));
}

