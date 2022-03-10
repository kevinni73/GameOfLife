#pragma once
#include "Coords.h"
#include <stdint.h>
#include <unordered_set>
#include <unordered_map>

class Grid {
public:
	void SetAlive(int64_t x, int64_t y);
	void SimulateStep();

	// Utility functions
	void Display(int halfNum);
	void Print();
private:
	void SetAlive(int64_t x, int64_t y, std::unordered_set<Coords>& alive, std::unordered_map<Coords, unsigned char>& neighbors);

	// if memory extremely tight, we could combine the set and map
	// leveraging the unused bits in the unsigned char + bit manipulation
	std::unordered_set<Coords> _alive;
	std::unordered_map<Coords, unsigned char> _neighbors;
};
