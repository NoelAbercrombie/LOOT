#include "game.h"
#include "system.h"
#include "render.h"
#include "battle.h"
#include "menu.h"
#include "player.h"
#include "world.h"
#include "direction.h"
#include "button.h"
#include "cutscenes.h"
#include "gamestate.h"

Game::Game(System & ab, Render & render, Menu & menu, Player & player, World & world, Cutscenes & cutscenes, Battle & battle)
{
  this->ab = &ab;
  this->menu = &menu;
  this->render = &render;
  this->player = &player;
  this->world = &world;
  this->cutscenes = &cutscenes;
  this->battle = &battle;
}


void Game::save(const bool slot)
{

}
void Game::load(const bool slot)
{

}

void Game::step(void)
{
    switch(ab->getState())
    {
  		case GameState::Menu:
  		{
  			if (ab->stateChanged())
  			{
  				menu->init();
  				ab->stateEndChange();
  			}
  			menu->step();
  			menu->draw();
  			break;
  		}
  		case GameState::Gameplay:
  		{
  			if (ab->getLastState() == GameState::Menu)
  			{
  				player->init();
  				world->init();
  				ab->stateEndChange();
  			}
  			render->step();
  			render->draw();
        //Putting the player code at the end adds 1 frame of latency to player movement, but reduces flicker between input & certain responses.
        player->resetMoved();
        player->step();     
  			break;
  		}
  		case GameState::Battle:
  		{
        if (ab->getLastState() == GameState::Gameplay) //cheaper than checking if last frame was not battle
        {
          battle->start();
          ab->stateEndChange();
        }
  			battle->step();
  			render->drawView();
  			battle->draw();
        break;
  		}
      case GameState::Cutscene:
      {
        cutscenes->step();
        if(cutscenes->drawView)
        {
          render->draw();
        }
        cutscenes->draw();
        break;
      }
    }
}
