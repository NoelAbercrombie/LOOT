#pragma once
#include <stdint.h>
#include "chest.h"
#include "itemtype.h"
#include "tiletype.h"


class World
{
  private:
    uint8_t battleTendency;
  public:
    uint8_t width,height;
    TileType level[128]; //biggest map size, 16*16, 32*8, etc
    ChestList chests;
    uint8_t itemType[16];
    uint8_t itemAction[16]; // I don't even want to know how an arbitrary number is supposed to represent an action

    void init(void);
    void step(void);

    //map stuff
    void load(uint8_t *ID);
    void set(const int8_t x, const int8_t y, const TileType type);
    void setFast(const int8_t x, const int8_t y, const TileType type);
    bool validSize(const uint8_t width, const uint8_t height);
    TileType get(const int8_t x, const int8_t y) const;
    TileType getFast(const int8_t x, const int8_t y) const;
    bool inbound(const int8_t x, const int8_t y) const;

    //battle stuff
    uint8_t getBattleChance(void);

    //item stuff
    void setItem(const uint8_t item, const int8_t x, const int8_t y, const ItemType type);
    ItemType getItemType(const int8_t x, const int8_t y);
    uint8_t getItemID(const int8_t x, const int8_t y);
    // This should be 'hasItem',
    // 'getItem' implies you can actually retrieve a reference to said item
    bool hasItem(const int8_t x, const int8_t y) const;

    void takeItem(const uint8_t item);
    void removeItem(const uint8_t item);
};
