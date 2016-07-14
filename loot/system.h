#pragma once

#include "arduboy.h"
#include "constants.h"
#include "button.h"

#define SCREEN_WIDTH  (WIDTH)
#define SCREEN_HEIGHT (HEIGHT)

class System : public Arduboy
{
  private:
  uint8_t nowInput, prevInput, lastState, state;

  public:
  // Explicitly calling parent's default constructor for the sake of clarity.
  // Arduboy's constructor would be called even if the exlicit call were removed.
  System(void) : Arduboy()
  {
    this->lastState = stateNull;
    this->state = stateMenu;  //begin on the menu
    this->nowInput  = 0x00;
    this->prevInput = 0xff;
    this->setFrameRate(30); // I checked, it's safe to do this
  }

  void update(void)
  {
    //input
    this->prevInput = this->nowInput;
    this->nowInput  = buttonsState();

    // Remapping the button byte every frame is a big waste of time, just use the native bit arrangement
    // Not to mention every one of these function calls was reading from 3 input pins each time, just to arrive
    // at the same result each time. That's 6 times the necessary number of instructions.

    // if(arduboy.pressed(UP_BUTTON)) { nowInput |= BTN_U; }
    // if(arduboy.pressed(DOWN_BUTTON)) { nowInput |= BTN_D; }
    // if(arduboy.pressed(LEFT_BUTTON)) { nowInput |= BTN_L; }
    // if(arduboy.pressed(RIGHT_BUTTON)) { nowInput |= BTN_R; }
    // if(arduboy.pressed(A_BUTTON)) { nowInput |= BTN_A; }
    // if(arduboy.pressed(B_BUTTON)) { nowInput |= BTN_B; }
  }

  bool isPressed(const Button button) const
  {
     return ((this->nowInput & static_cast<uint8_t>(button)) != 0);
  }

  bool isPushed(const Button button) const
  {
    // If pressed this frame, but not last frame
    return ((this->nowInput & static_cast<uint8_t>(button)) != 0) && ((this->prevInput & static_cast<uint8_t>(button)) == 0);
  }

  bool isReleased(const Button button) const
  {
    // If released in the last frame
    return ((this->prevInput & static_cast<uint8_t>(button)) != 0) && ((this->nowInput & static_cast<uint8_t>(button)) == 0);
  }

  void drawSprite(const int8_t x, const int8_t y, const byte* bitmap, const byte c)
  {
    this->drawBitmap(x ,y , bitmap+2, pgm_read_byte(bitmap), pgm_read_byte(bitmap+1), c);
  }

  void drawSpriteMasked(const int8_t x, const int8_t y, const byte* bitmap, const byte* mask)
  {
    const int8_t w = pgm_read_byte(bitmap);
    const int8_t h = pgm_read_byte(bitmap+1);
    this->drawBitmap(x, y, mask+2, w, h, 0);
    this->drawBitmap(x, y, bitmap+2, w, h, 1);
  }

  void drawSpriteCentered(const int8_t x, const int8_t y, const byte* bitmap, const byte c)
  {
    const int8_t hw = pgm_read_byte(bitmap) / 2;
    const int8_t hh = pgm_read_byte(bitmap+1) / 2;
    this->drawSprite(x-hw, y-hh, bitmap, c);
  }
  void drawSpriteMaskedCentered(const int8_t x, const int8_t y, const byte* bitmap, const byte* mask)
  {
    const int8_t hw = pgm_read_byte(bitmap) / 2;
    const int8_t hh = pgm_read_byte(bitmap+1) / 2;
    this->drawSprite(x - hw, y - hh, mask, 0);
    this->drawSprite(x - hw, y - hh, bitmap, 1);
  }

  uint8_t getState(void) const
  {
    return this->state;
  }

  uint8_t getLastState(void) const
  {
    return this->lastState;
  }

  bool stateChanged(void) const
  {
    if(this->state != this->lastState)
      Serial.println(state);
    return (this->state != this->lastState);
  }

  void setState(const uint8_t newstate)
  {
    this->lastState = this->state;
    this->state = newstate;
  }

  void stateEndChange(void)
  {
    this->lastState = this->state;
  }
};
