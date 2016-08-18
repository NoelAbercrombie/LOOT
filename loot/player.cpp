#include "player.h"
#include "world.h"
#include "system.h"
#include "direction.h"
#include "TileType.h"

Player::Player(System & ab, World & world)
{
  this->ab = &ab;
  this->world = &world;
}

void Player::init(void)
{
  moved = true;
  x = 1;
  y = 1;
  hpMax = 10;
  spMax = 10;
  hp = 10;
  sp = 10;
}

Direction Player::getDirection(void) const
{
  return dir;
}

void Player::changeDirection(const Direction direction)
{
  Direction lastDir = this->dir;
  this->dir = direction;
  this->moved = (this->dir != lastDir);
}

bool Player::hasMoved(void) const
{
 return moved;
}

void Player::resetMoved(void)
{
  moved = false;
}

void Player::move(const int8_t distance)
{
  int8_t ny = 0, nx = 0;
  switch(this->dir)
  {
    case Direction::East: nx = distance;  break;
    case Direction::South: ny = distance;break;
    case Direction::West: nx = -distance; break;
    case Direction::North: ny = -distance; break;
  }
  this->jump(this->x + nx, this->y + ny);
  this->battleSteps += abs(distance);
}

void Player::jump(const uint8_t x, const uint8_t y)
{
  if (world->get(x, y) == TileType::None)
  {
    this->x = x;
    this->y = y;
    moved = true;
  }
}

void Player::step()
{
  Direction lastDir = dir;

  if(ab->isPushed(Button::Left))
    dir = rotateLeft(dir);

  if(ab->isPushed(Button::Right))
    dir = rotateRight(dir);

  if(dir != lastDir)
  {
    moved = true;
  }

  if(ab->isPushed(Button::Up)) //move 1 step in the looking direction
    move(1);

  if(ab->isPushed(Button::Down))
    move(-1);

  if(moved)
  {
    Serial.println(battleSteps);
    if (world->hasItem(x,y))
    {
      Serial.print(F("Item! Type : "));
      Serial.print(static_cast<uint8_t>(world->getItemType(x,y)));
      Serial.print(F(" ID : "));
      Serial.println(world->getItemID(x,y));
    }
    else if (random(battleSteps) > world->getBattleChance())
    { 
      ab->setState(GameState::Battle);
      Serial.println(F("Battle!"));
      battleSteps = 0;
    }
  }
}
