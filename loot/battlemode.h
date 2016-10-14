#pragma once
#include <stdint.h>

enum class battleType : uint8_t
{
	None,
	Start,
	Select,
	Attack,
	Items,
	Run,
	PlayerTurn,
	EnemyTurn,
	Win,
	Lose,
};