#pragma once
#include <stdint.h>

enum class battleMode : uint8_t
{
	None,
	Menu,
	Run,
	PlayerTurn,
	EnemyTurn,
	Win,
	Lose,
};