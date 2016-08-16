#pragma once
#include <stdint.h>

#if defined(ARDUBOY_2_LIB) 
#include "ArduboyCore.h"
#else
#include <core/core.h>
#endif

enum class Button : uint8_t
{
	None = 0,
	Up = (UP_BUTTON),
	Down = (DOWN_BUTTON),
	Left = (LEFT_BUTTON),
	Right = (RIGHT_BUTTON),
	A = (A_BUTTON),
	B = (B_BUTTON)
};
