#pragma once
#include <stdint.h>

#include "debug.h"

template <typename TItem, int8_t Capacity>
class List
{
public:
	static_assert(Capacity > 0, "Attempt to instantiate List with Capacity less than 1");

private:
	TItem items[Capacity];
	int8_t next;

public:
	int8_t getCount(void) const // O(1)
	{
	  return this->next;
	}

  // Consider marking constexpr
	int8_t getCapacity(void) const // O(1)
	{
	  return Capacity;
	}

	bool add(const TItem item) // O(1)
	{
		if (this->next == Capacity)
			return false;

		this->items[this->next] = item;
		++this->next;
	}

	void remove(const TItem item) // O(n)
	{
		auto index = this->indexOf(item);
		if (index != -1)
		  this->removeAt(index);
	}

	void removeAt(const int8_t index) // O(n)
	{
		DEBUG_ASSERT(index >= 0);
		DEBUG_ASSERT(index < Capacity);
		DEBUG_ASSERT(index < this->next);

		for(uint8_t i = index; i < this->next; ++i)
			this->items[i] = this->items[i + 1];
		--this->next;	
	}

	bool contains(const TItem item) // O(n)
	{
		return this->indexOf(item) != -1;
	}

	// Returns -1 if item not found
	int8_t indexOf(const TItem item) // O(n)
	{
		for (uint8_t i = 0; i < this->next; ++i)
			if (this->items[i] == item)
				return i;

		return -1;
	}

	TItem & operator [] (const uint8_t index) // O(1)
	{
		DEBUG_ASSERT(index >= 0);
		DEBUG_ASSERT(index < Capacity);
		DEBUG_ASSERT(index < this->next);

		return this->items[index];
	}

	const TItem & operator [] (const uint8_t index) const // O(1)
	{
		DEBUG_ASSERT(index >= 0);
		DEBUG_ASSERT(index < Capacity);
		DEBUG_ASSERT(index < this->next);

		return this->items[index];
	}
};
