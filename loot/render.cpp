#include "system.h"
#include "graphics.h"
#include "gamestate.h"
#include "render.h"
#include "world.h"
#include "player.h"
#include "direction.h"
#include "tiletype.h"
#include "itemtype.h"


Render::Render(System & ab, World & world, Player & player)
{
  this->ab = &ab;
  this->world = &world;
  this->player = &player;
}

inline bool Render::wallCheck(const int8_t x, const int8_t y)
{
  return (world->get(x, y) != TileType::None);
}
inline bool Render::itemCheck(const int8_t x, const int8_t y)
{
  return (world->hasItem(x, y));
}

void Render::calculateView(const int8_t x, const int8_t y, const Direction dir)
{
  /*
  if (dir == 0)
  {
    xs[0]=+3; xs[1]=+3; xs[2]=+3; xs[3]=+2; xs[4]=+2; xs[5]=+2; xs[6]=+1; xs[7]=+1; xs[8]=+1; xs[9]=0; xs[10]=0; xs[11]=0;
    ys[0]=-1; ys[1]=0;   ys[2]=+1; ys[3]=-1; ys[4]=0; ys[5]=+1; ys[6]=-1; ys[7]=0; ys[8]=+1; ys[9]=-1; ys[10]=0; ys[11]=+1;
  }
  if (dir == 1)
  {
    xs[0]=+1; xs[1]=0; xs[2]=0-1; xs[3]=+1; xs[4]=0; xs[5]=-1; xs[6]=+1; xs[7]=0; xs[8]=-1; xs[9]=+1; xs[10]=0; xs[11]=-1;
    ys[0]=+3; ys[1]=+3; ys[2]=+3; ys[3]=+2; ys[4]=+2; ys[5]=+2; ys[6]=+1; ys[7]=+1; ys[8]=+1; ys[9]=0; ys[10]=0; ys[11]=0;
  }
  if (dir == 2)
  {
    xs[0]=-3; xs[1]=-3; xs[2]=-3; xs[3]=-2; xs[4]=-2; xs[5]=-2; xs[6]=-1; xs[7]=-1; xs[8]=-1; xs[9]=0; xs[10]=0; xs[11]=0;
    ys[0]=+1; ys[1]=0; ys[2]=-1; ys[3]=+1; ys[4]=0; ys[5]=-1; ys[6]=+1; ys[7]=0; ys[8]=-1; ys[9]=+1; ys[10]=0; ys[11]=-1;
  }
  if (dir == 3)
  {
    xs[0]=-1; xs[1]=0; xs[2]=+1; xs[3]=-1; xs[4]=0; xs[5]=+1; xs[6]=-1; xs[7]=0; xs[8]=+1; xs[9]=-1; xs[10]=0; xs[11]=+1;
    ys[0]=-3; ys[1]=-3; ys[2]=-3; ys[3]=-2; ys[4]=-2; ys[5]=-2; ys[6]=-1; ys[7]=-1; ys[8]=-1; ys[9]=0; ys[10]=0; ys[11]=0;
  }
  */
  static const int8_t arrA[12] = { 3, 3, 3, 2, 2, 2, 1, 1, 1, 0, 0, 0 };
  static const int8_t arrB[12] = { -1, 0, +1, -1, 0, +1, -1, 0, +1, -1, 0, +1 };

  int8_t xs, ys;
  for(uint8_t i = 0; i < 12; ++i)
  {
    switch(dir)
    {
      case Direction::East: { xs = arrA[i]; ys = arrB[i]; break; }
      case Direction::South: { xs = -arrB[i]; ys = arrA[i]; break; }
      case Direction::West: { xs = -arrA[i]; ys = -arrB[i]; break; }
      case Direction::North: { xs = arrB[i]; ys = -arrA[i]; break; }
    }

    wallShow[i] = wallCheck(x + xs, y + ys);
    itemShow[i] = false;

    if(wallShow[i] == false)
      itemShow[i] = itemCheck(x + xs, y + ys);
  }


  wallShow[10] = false; //position player is standing on

  if (wallShow[7])  //speed up by disabling hidden walls
  {
    wallShow[4] = false;
    wallShow[0] = false;
    wallShow[2] = false;
  }
  if (wallShow[4])
  {
    wallShow[1] = false;
  }
}

void Render::step(void)
{
}

void Render::draw(void)
{
  if(player->hasMoved()) //only recalculate on movement
   {
     calculateView(player->x, player->y, player->getDirection());
   }
  drawView();
  drawMap();
}

void Render::drawView(void)
{
  const uint8_t wallSize[] = { 6, 10, 18, 32, 64 };  //size in pixels of each step
  uint8_t wall = 0;  //current wall

  int8_t left = 0, leftBack = 0;
  for(uint8_t i = 0; i < 4; ++i) //distance
  {
    const uint8_t backSize = wallSize[i + 0]; // Size of the backside of the walls, for depth
    const uint8_t drawSize = wallSize[i + 1]; // Size of walls on screen
    const uint8_t halfBackSize = backSize / 2;
    const uint8_t halfSize = drawSize / 2;
    const uint8_t topBack  = 32 - halfBackSize;         // Y position of the walls on screen
    const uint8_t top      = 32 - halfSize;
    leftBack = 32 - (halfBackSize * 3);      // X position of the walls on screen
    left     = 32 - (halfSize * 3);

    for(uint8_t n = 0; n < 3; ++n) // left -> right
    {
      if (wallShow[wall]) //if wall exists, draw it
      {
        if((n == 0) && (wallShow[wall + 1] == 0))  //left wall, only draw if the middle wall is missing
        {
          ab->fillRect(left + drawSize, top, (leftBack + backSize) - (left + drawSize), drawSize, 0); //blank out area behind wall
          ab->drawLine(left + drawSize, top, leftBack + backSize, topBack, 1);                     //upper line
          ab->drawLine(leftBack + backSize, topBack + backSize, left + drawSize, top + drawSize, 1); //lower line
          ab->drawLine(leftBack + backSize, topBack, leftBack + backSize, topBack + backSize, 1); //far line
        }
        if((n == 2) && (wallShow[wall - 1] == 0)) //right wall, ditto
        {
          ab->fillRect(leftBack, top, left - leftBack, drawSize, 0);
          ab->drawLine(leftBack, topBack, left, top, 1);     //upper
          ab->drawLine(leftBack, topBack + backSize, left, top + drawSize, 1); //lower
          ab->drawLine(leftBack, topBack, leftBack, topBack + backSize, 1);  //side
        }
        if(wallShow[wall + 3] == 0)  // Draw flat wall if not immediately next to the camera, and if there is no wall infront
        {          
          int width = (left + drawSize > System::ScreenCentreX) ? 15 : drawSize; // Keep wall inside render area
          ab->fillRect(left, top, width + 0, drawSize + 0, 0); // Blank out wall area
          ab->drawRect(left, top, width + 1, drawSize + 1, 1); // Draw wall outline
        }
      } 
      else if(itemShow[wall])
      {
        int8_t itemx = (left + drawSize / 4);
        if(itemx < 64)
        {
          int8_t itemy = (top + drawSize) - (drawSize/2);
          //const uint8_t * image[];
          const uint8_t * image;
          const uint8_t * mask;
          switch(i)
          {
            case 0: image = imgChest0;  mask = imgBlank;  break;
            case 1: image = imgChest1;  mask = imgBlank;  break;
            case 2: image = imgChest2;  mask = imgChest2Mask; break;
            case 3: image = imgChest3;  mask = imgChest3Mask; break;
          };
          ab->drawSpriteMasked(itemx,itemy,image,mask);
          //ab->drawRect(itemx, itemy, drawSize / 2, drawSize / 2, 1);
        }
      }
      ++wall;
      left += drawSize;     //advance left positions
      leftBack += backSize;
    }
  }
  ab->fillRect(System::ScreenCentreX, 0, 16, System::ScreenHeight, 0);  //hide any leaky drawing
  ab->drawRect(0, 0, System::ScreenWidth / 2, System::ScreenHeight, 1);

  if(ab->getState() != GameState::Battle)
  {
    #if defined(CHAR_COMPASS)
    char c = '\0';
    switch(player->getDirection())
    {
      case Direction::North: { c = 'N'; break; }
      case Direction::East:  { c = 'E'; break; }
      case Direction::South: { c = 'S'; break; }
      case Direction::West:  { c = 'W'; break; }
    }
    ab->drawChar(32 - (5 / 2), (7 / 2), c, 1, 0, 1);
    #else
    const uint8_t * image;
    switch(player->getDirection())
    {
      case Direction::North: { image = imgCompassN; break; }
      case Direction::East:  { image = imgCompassE; break; }
      case Direction::South: { image = imgCompassS; break; }
      case Direction::West:  { image = imgCompassW; break; }
    }
    ab->drawSpriteCentred(32, 6, image, 1);
    #endif
  }
}

void Render::drawMap(void)
{
  // Out of interest, making this value 64 instead of 63 adds 2 bytes to the code and I have no idea why.
  // Presumably it's a limitation of the AVR instruction set. AVR probably only affords 5 bits to immediate values.
  constexpr static const uint8_t offsetx = System::ScreenCentreX;
  // Draw map grid
  for(int iy = 0, jy = 0; iy < 8; ++iy, jy += 8)
    for(int ix = 0, jx = 0; ix < 8; ++ix, jx += 8)
      if (wallCheck(ix,iy))
        ab->drawRect(offsetx + jx, jy, 9, 9, 1);

  { // Explicit scoping in the hopes the compiler will ditch these 6 variables asap
    // x3 and y3 refer to the point of the arrow. Only 6 coords are needed for 3 points
    // By adding 2 to x and y up here, 10 addition operations can be eliminated
    uint8_t x1 = offsetx + (player->x * 8) + 2;
    uint8_t y1 = (player->y * 8) + 2;
    uint8_t x2 = x1, y2 = y1;
    uint8_t x3 = x1, y3 = y1;

    switch(player->getDirection())
    {
      case Direction::East:
      {
        /*x1 += 0;*/ /*y1 += 0;*/
        /*x2 += 0;*/ y2 += 4;
        x3 += 4; y3 += 2;
        break;
      }
      case Direction::South:
      {
        /*x1 += 0;*/ /*y1 += 0;*/
        x2 += 4; /*y2 += 0;*/
        x3 += 2; y3 += 4;
        break;
      }
      case Direction::West:
      {
        x1 += 4; /*y1 += 0;*/
        /*x2 += 0;*/ y2 += 2;
        x3 += 4; y3 += 4;
        break;
      }
      case Direction::North:
      {
        /*x1 += 0;*/ y1 += 4;
        x2 += 2; /*y2 += 0;*/
        x3 += 4; y3 += 4;
        break;
      }
    }
    ab->drawLine(x1, y1, x3, y3, 1);
    ab->drawLine(x2, y2, x3, y3, 1);
    ab->drawLine(x1, y1, x2, y2, 1);
  }

  // Outlines the map
  ab->drawRect(offsetx, 0, System::ScreenWidth/2, System::ScreenHeight, 1);
}

void Render::drawStats(void)
{
  ab->setCursor(System::ScreenCentreX + 2, 2);
  ab->print(F("HP : "));
  ab->setCursor(System::ScreenCentreX + 2, 10);
  ab->print(F("SP : "));
  ab->setCursor(System::ScreenCentreX + 2, 18);
  ab->print(F("G  : "));
}
