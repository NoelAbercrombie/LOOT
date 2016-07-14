#pragma once
#include <stdint.h>
#include "direction.h"

class System;
class World;
class Player;

class Render
{
  private:
    System * ab;
    World * world;
    Player * player;

    bool wallShow[11] = {};
    bool itemShow[11] = {};
  public:
    Render(System & ab,World & world,Player & player);

    void step(void);
    void draw(void);

    bool wallCheck(const int8_t x, const int8_t y);
    uint8_t itemCheck(const int8_t x, const int8_t y);
    void calculateView(const int8_t x, const int8_t y, const Direction dir);
    void drawView(void);
    void drawMap(void);
    void drawStats(void);
};
