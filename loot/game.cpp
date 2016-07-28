#include "game.h"
#include "system.h"
#include "render.h"
#include "battle.h"
#include "menu.h"
#include "player.h"
#include "world.h"
#include "direction.h"
#include "button.h"
#include "gamestate.h"

Game::Game(System & ab, Render & render, Menu & menu, Player & player, World & world, Battle & battle)
{
  this->ab = &ab;
  this->menu = &menu;
  this->render = &render;
  this->player = &player;
  this->world = &world;
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
  			player->step();
  			render->step();
  			render->draw();
  			player->resetMoved();
  			break;
  		}
  		case GameState::Battle:
  		{
  			battle->step();
  			render->drawView();
  			battle->draw();
  		}
    }
}
