//Here in a vain attempt to reduce .h spam clutter
#pragma once
#include <stdint.h>

enum class battleMenu : uint8_t
{
	Top,
	Fight,
	Item,
	Run,
}

enum class battleMode : uint8_t
{
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