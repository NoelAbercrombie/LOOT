#pragma once

#include "arduboy2.h"
#include "gamestate.h"
#include "button.h"

#if defined(ARDUBOY_2_LIB) 
class System : public Arduboy2
#else
class System : public Arduboy
#endif
{
	private:
		uint8_t nowInput;
		uint8_t prevInput;
		GameState lastState;
		GameState state;

	public:  
		constexpr static const uint8_t ScreenWidth = WIDTH;
		constexpr static const uint8_t ScreenHeight = HEIGHT;
		constexpr static const uint8_t ScreenCentreX = ScreenWidth / 2;
		constexpr static const uint8_t ScreenCentreY = ScreenHeight / 2;

	public:
		// Explicitly calling parent's default constructor for the sake of clarity.
		// Arduboy's constructor would be called even if the explicit call were removed.
		#if defined(ARDUBOY_2_LIB) 
		System(void) : Arduboy2()
		#else
		System(void) : Arduboy()
		#endif
		{
			this->lastState = GameState::Null;
			this->state = GameState::Menu;
			this->nowInput  = 0x00;
			this->prevInput = 0xff;
			this->setFrameRate(30); // I checked, it's safe to do this
		}
  
		void update(void)
		{
			this->prevInput = this->nowInput;
			this->nowInput  = this->buttonsState();
		}
		
		bool isPressed(const Button button) const
		{
			return ((this->nowInput & static_cast<uint8_t>(button)) != 0);
		}
  
		bool isPushed(const Button button) const
		{
			return
				((this->nowInput & static_cast<uint8_t>(button)) != 0) &&
				((this->prevInput & static_cast<uint8_t>(button)) == 0);
		}
  
		bool isReleased(const Button button) const
		{
			return
				((this->nowInput & static_cast<uint8_t>(button)) == 0) &&
				((this->prevInput & static_cast<uint8_t>(button)) != 0);
		}
  
		void drawSprite(const int8_t x, const int8_t y, const uint8_t * bitmap, const uint8_t colour) 
		{
			this->drawBitmap(x ,y , bitmap + 2, pgm_read_byte(bitmap + 0), pgm_read_byte(bitmap + 1), colour);
		}
  
		void drawSpriteMasked(const int8_t x, const int8_t y, const uint8_t * bitmap, const uint8_t * mask)
		{
			this->drawBitmap(x, y, mask + 2, pgm_read_byte(bitmap + 0), pgm_read_byte(bitmap + 1), 0);
			this->drawBitmap(x, y, bitmap + 2, pgm_read_byte(bitmap + 0), pgm_read_byte(bitmap + 1), 1);
		}
    
		void drawSpriteCentred(const int8_t x, const int8_t y, const uint8_t * bitmap, const uint8_t colour)
		{  
			const int8_t w = pgm_read_byte(bitmap + 0);
			const int8_t h = pgm_read_byte(bitmap + 1);
			this->drawBitmap(x - (w / 2), y - (h / 2), bitmap + 2, w, h, colour);
		}  
  
		void drawSpriteMaskedCentered(const int8_t x, const int8_t y, const uint8_t * bitmap, const uint8_t * mask)
		{  
			const int8_t w = pgm_read_byte(bitmap + 0);
			const int8_t h = pgm_read_byte(bitmap + 1);
			this->drawBitmap(x - (w / 2), y - (h / 2), mask + 2, w, h, 0);
			this->drawBitmap(x - (w / 2), y - (h / 2), bitmap + 2, w, h, 1);
		}
  
		GameState getState(void) const
		{
			return this->state;
		}
  
		GameState getLastState(void) const
		{
			return this->lastState;
		}
		
		void revertState(void) 
		{
			this->state = this->lastState;
		}
  
		bool stateChanged(void) const
		{
			return (this->state != this->lastState);
		}
  
		void setState(const GameState newstate)
		{
			this->lastState = this->state;
			this->state = newstate;
		}
  
		void stateEndChange(void)
		{
			this->lastState = this->state;
		}
};
