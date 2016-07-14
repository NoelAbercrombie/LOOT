#include "game.h"
#include "system.h"
#include "render.h"
#include "menu.h"
#include "player.h"
#include "world.h"
#include "constants.h"
#include "direction.h"
#include "button.h"

Game::Game(System & ab, Render & render, Menu & menu, Player & player, World & world)
{
  this->ab = &ab;
  this->menu = &menu;
  this->render = &render;
  this->player = &player;
  this->world = &world;
}

void Game::save(const bool slot)
{

}
void Game::load(const bool slot)
{

}

void Game::step(void)
{
  if (ab->stateChanged())
  {
    auto state = ab->getState();
    switch(state)
    {
      case stateMenu:
      {
        menu->init();
        break;
      }
      case stateGame:
      {
        if (ab->getLastState() == stateMenu)
        {
          player->init();
          world->init();
          break;
        }
      }
      case stateBattle:
      {
      }
    }
  }
  ab->stateEndChange();

  switch(ab->getState())
  {
    case stateMenu:
    {
      menu->step();
      menu->draw();
      break;
    }
    case stateGame:
    {
      player->step(ab->isPushed(Button::Up), ab->isPushed(Button::Down), ab->isPushed(Button::Left), ab->isPushed(Button::Right), ab->isPushed(Button::A));
      world->step();
      render->step();
      render->draw();
      player->resetMoved();
      break;
    }
    case stateBattle:
    {
      render->drawView();
      ab->drawRect(24,40,17,16,1);  //enemy placement test
      ab->setCursor(66,2);
      ab->print(F("Battle"));
      ab->setCursor(66,10);
      ab->print(F("goes here!"));
      if(ab->isPushed(Button::A))
        ab->setState(stateGame);
      break;
    }
  }
}
