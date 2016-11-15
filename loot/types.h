//Here in a vain attempt to reduce .h spam clutter
#pragma once
#include <stdint.h>

enum class battleMenu : uint8_t
{
	Top=0,
	Fight=1,
	Item=2,
	Run=3,
};

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