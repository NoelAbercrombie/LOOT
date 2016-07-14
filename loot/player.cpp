#include "player.h"
#include "world.h"
#include "system.h"
#include "direction.h"

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
  int8_t nx, ny;  //calculate direction
  switch(this->dir)
  {
    case Direction::East: nx = 1; break;
    case Direction::South: ny = 1; break;
    case Direction::West: nx = -1; break;
    case Direction::North: ny = -1; break;
  }
  this->jump(this->x + (nx * distance), this->y + (ny * distance));
  this->battleSteps += abs(distance);
}

void Player::jump(const uint8_t x, const uint8_t y)
{
  if (world->get(x, y) == 0)
  {
    this->x = x;
    this->y = y;
    moved = true;
  }
}

void Player::step(const bool up, const bool down, const bool left, const bool right, const bool a)
{
  Direction lastDir = dir;

  if(left)
    dir = rotateLeft(dir);

  if(right)
    dir = rotateRight(dir);

  if(dir != lastDir)
  {
    moved = true;
  }

  if(up) //move 1 step in the looking direction
    move(1);

  if(down)
    move(-1);

  if(world->getItem(x,y))
  {
    Serial.println(F("Item!"));
    //ab->fillScreen(0);
    //world->setItem(world->getItemID(x,y),x,y,0);
  }

  if(moved)
  {
    Serial.println(battleSteps);
    if (!(world->getItem(x,y)) && (random(battleSteps) > world->getBattleChance()) )
    { 
      Serial.println(F("Battle!"));
      battleSteps = 0;
    }
  }

}
