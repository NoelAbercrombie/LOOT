#include "cutscenes.h"
#include "cutscenetype.h"
#include "gamestate.h"
#include "system.h"
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
}

/*
void Cutscenes::play(const CutsceneType scene)
{
	//interrupts current state to play a cutscene.
	start(scene, ab->getState());
}
*/

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
	}
}