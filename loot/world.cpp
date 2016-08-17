#include <stdint.h>
#include <Arduino.h>
#include "world.h"
#include "chest.h"
#include "itemtype.h"

//world
void World::init(void)
{
  width = 8;
  height = 8;

  // Replace this bit with a progmem loader doodah
  static const uint8_t leveldata[64] =
  {
    1,1,1,1,1,1,1,1,
    0,0,0,0,0,1,0,0,
    1,1,0,1,1,0,0,1,
    1,0,0,0,0,0,1,0,
    1,1,0,1,1,1,1,0,
    1,0,0,0,0,0,0,0,
    1,0,1,1,1,1,1,0,
    1,1,1,1,1,1,1,0
  };
  for(uint8_t i=0; i<64; ++i)
  {
    level[i] = static_cast<TileType>(leveldata[i]);
  };
  battleTendency = 4;

  // Creates a chest and adds it straight to the list
  chests.add(Chest(0, 1, ItemType::TestItem));
  chests.add(Chest(1, 6, ItemType::TestItem2));
  Serial.print(F("Chest num : "));
  Serial.println(chests.getCount());
}

void World::load(uint8_t *ID) //reads a map from PROGMEM and loads it into memory
{
  /*
  width = pgm_read_byte(*ID);
  height = pgm_read_byte(*ID+1);

  player.x = pgm_read_byte(*ID+2);
  player.y = pgm_read_byte(*ID+3);

  int length = width*height;
  for(i=0; i<length; ++i)
  {
    level[i] = pgm_read_byte((*ID+4)+i);
  }
  */
}

bool World::validSize(const uint8_t width, const uint8_t height)  //will our world fit in RAM? Probably unneeded if the maps are precomputed
{
  return (width*height <= 256);
}

void World::set(const int8_t x, const int8_t y, const TileType type)
{
  if(inbound(x,y))
    level[(y*width)+x] = type;
}

void World::setFast(const int8_t x, const int8_t y, const TileType type)
{
  level[(y*width)+x] = type;
}

TileType World::get(const int8_t x, const int8_t y) const
{
  if(inbound(x,y))
    return level[(y*width)+x];
  else
    return TileType::Wall;  //outside the map is a sea of walls
}
TileType World::getFast(const int8_t x, const int8_t y) const
{
  return level[(y*width)+x];
}

bool World::inbound(const int8_t x, const int8_t y) const
{
  return((x>=0)&&(y>=0)&&(x<width)&&(y<height));
}

void World::step(void)
{

}


////battle stuff
uint8_t World::getBattleChance(void)
{
  return this->battleTendency;
}

//////
//BURN EVERYTHING BELOW THIS LINE
/////

ItemType World::getItemType(const int8_t x, const int8_t y) const
{
  //this is horrible please change
  for(uint8_t i; i<16; ++i) //loop every chest
  {
    // As if by magic these former array indexers are now indexing a list.
    // This is one of those cases where if you wield the chainsaw correctly
    // you'll cut the tree and not your fingers.
    if ((chests[i].getX() == x) && (chests[i].getY() == y)) //if chest is on position, return contents
      return (chests[i].getType());
  }
  return ItemType::None;
}

// If this was actually returning a reference the chest, you could use that in the getItemType function.
// Or better yet you could let the caller check the type directly from the returned chest.
// Also, please remind me to one day educate you on the wonders of Haskell's Maybe type 
// and why C++17 is introducing a std::optional type.
bool World::hasItem(const int8_t x, const int8_t y) const
{
  for(uint8_t i; i<16; ++i) //loop every chest
  {
    if ((chests[i].getX() == x) && (chests[i].getY() == y))
      return true;
  }
  return false;
}

// How this is actually legal without a default return value is a mystery
// I'd recommend assigning 0 as the 'empty' or 'invalid' type if
// you don't change this to an enum
uint8_t World::getItemID(const int8_t x, const int8_t y) const
{
  //Will act weirdly if no chest on tile; 0 is a valid id
  for(uint8_t i; i<16; ++i) //loop every chest
  {
    if ((chests[i].getX() == x) && (chests[i].getY() == y))
      return i;
  }
  return 255;
}

// If you made Chest public you could just make this function accept an index and a Chest.
// Ultimately I'm concerned about other code being able to effectively overwrite all chests though.
// Maybe now ChestList is available you should change this to an add function that doesn't need an index
// and might potentially fail.
void World::setItem(const uint8_t item,const int8_t x, const int8_t y, const ItemType type)
{
  chests[item] = Chest(x,y,type);
}

void World::takeItem(const uint8_t item)
{
  //add inventory code here later
  removeItem(item);
}

void World::removeItem(const uint8_t item)
{
  chests.remove(item);
}