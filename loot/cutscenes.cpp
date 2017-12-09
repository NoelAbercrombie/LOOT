#include "cutscenes.h"
#include "cutscenetype.h"
#include "gamestate.h"
#include "system.h"
#include "render.h"
#include "button.h"
#include "graphics.h"

Cutscenes::Cutscenes(System & ab)
{
  this->ab = &ab;
}

void Cutscenes::start(const CutsceneType scene, const GameState stateNext)
{
	this->scene = scene;
	this->stateNext = stateNext; 
	this->stateLast = ab->getState();
	ab->setState(GameState::Cutscene);
	complete = false;
	time = 0;
	drawView = false;
}

void Cutscenes::play(const CutsceneType scene)
{
	//interrupts current state to play a cutscene.
	start(scene, ab->getState());
}

void Cutscenes::end()
{
	complete = true;
	if (stateNext != GameState::Null)
	{
		ab->setState(stateLast);	//I'm sorry.
		ab->setState(stateNext);
	}
}

void Cutscenes::step()
{
	switch(scene)
	{
		case CutsceneType::None:
		{
			end();
			break;
		}
		case CutsceneType::Scene1:
		{
			if(ab->isPushed(Button::A))
			{
				end();
			}
			break;
		}

		case CutsceneType::Credits:
		{
			if(ab->isPushed(Button::A))
			{
				end();
			}
			break;
		}

		case CutsceneType::OpenChest:
		{
			time++;
			drawView = true;	//draw background & UI
			if (time > 80) end();
		}
	}
}

void Cutscenes::draw()
{
	switch(scene)
	{
		/*
		case CutsceneType::None:
		{
			ab->fillScreen(1);
			break;
		}
		*/
		case CutsceneType::Scene1:
		{
			time++;
			ab->drawSprite(32,(int8_t)(time % 96)-32,imgStory1,1);
			break;
		}
		case CutsceneType::Credits:
		{
			if(time<128)	time++;
		    ab->setCursor(0,64-(time/2));
		    ab->print(F("LOOT! - Epic Dungeon\n\nProgramming :\n @bakagamedev\n Pharap\nArt/Design : \n Migz (Gamerguy) \n"));
		    break;
		}
		case CutsceneType::OpenChest:
		{
			int8_t xoffset = 31;
			int8_t yoffset = 43;
			bool draw = true;
			const uint8_t * sprite;
			if (time<32)
			{
				sprite = imgChest3;
				if(time<16)	{	yoffset -= (time^time)/16;	}
				else	{	int8_t t=(32-time);	yoffset -= (t^t)/16;	}
			}
			else
			{
				sprite = imgChest3_1;
				if (time > 40)
				{
					sprite = imgChest3_2;
					xoffset += 2;
					yoffset -= 2;
				}
				if (time > 60)
				{
					draw = (time % 2);
				}
			}
			if (draw)
				ab->drawSpriteMaskedCentered(xoffset,yoffset,sprite,imgChest3Mask);
		}
	}
}
