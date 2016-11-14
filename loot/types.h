//Here in a vain attempt to reduce .h spam clutter
#pragma once
#include <stdint.h>

enum class battleMode : uint8_t
{
	None,
	Load,
	Start,
	Select,
	Run,
	PlayerTurn,
	EnemyTurn,
	Win,
	Lose,
};

enum class EnemyType : uint8_t
{
	None,
	Skellybones,
};

