#pragma once
#include <stdint.h>

enum class GameState : uint8_t
{
	Null,
	Menu,
	ClassSelect,
	NameEntry,
	Gameplay,
	Battle,
	Story1,
};
