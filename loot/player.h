#pragma once
#include <stdint.h>
#include "direction.h"

class System;
class World;
class Cutscenes;

class Player
{
  private:
    System * ab;
    World * world;
    Cutscenes * cutscenes;

    bool moved;
    Direction dir;
    
  public:
    int8_t x, y; //needs to be signed so checking negative positions doesn't bug out
    uint8_t battleSteps;
    uint8_t hp, sp;
    char name[8];

  public:
    Player(System & ab, World & world, Cutscenes & cutscenes);

    void init(void);
    Direction getDirection(void) const;
    void changeDirection(const Direction direction);
    bool hasMoved(void) const;
    void resetMoved(void);
    void move(const int8_t distance);
    void jump(const uint8_t x, const uint8_t y);
    void step();
};
