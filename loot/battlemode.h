#pragma once
#include <stdint.h>

enum class battleState : uint8_t
{
	Start,
	Select,
	Items,
	Run,
	PlayerTurn,
	EnemyTurn,
	Win,
	Lose,
};