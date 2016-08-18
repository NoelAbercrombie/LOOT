#pragma once
#include <stdint.h>
#include "list.h"
#include "itemtype.h"

class Chest
{
private:
    ItemType type;
    int8_t x;
    int8_t y;

public:
    Chest(void) = default;
    Chest(const int8_t x, const int8_t y, const ItemType type)
    {
      this->x = x;
      this->y = y;
      this->type = type;
    }
    
    ItemType getType(void) const
    {
      return type;
    }
    
    void setType(const ItemType type)
    {
      this->type = type;
    }
    
    int8_t getX(void) const
    {
      return x;
    }
    
    void setX(const int8_t x)
    {
      this->x = x;
    }
    
    int8_t getY(void) const
    {
      return y;
    }
    
    void setY(const int8_t y)
    {
      this->y = y;
    }

    bool onPosition(const int8_t x, const int8_t y) const
    {
      return (this->x == x && this->y == y);
    }
};

using ChestList = List<Chest, 16>;
