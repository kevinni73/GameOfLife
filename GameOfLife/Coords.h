#pragma once
#include <stdint.h>
#include <functional>

struct Coords {
	Coords() = default;
	Coords(int64_t xIn, int64_t yIn) {
		x = xIn;
		y = yIn;
	}

	bool operator==(const Coords& other) const {
		return (x == other.x && y == other.y);
	}

	int64_t x;
	int64_t y;
};

namespace std {
	template<>
	struct std::hash<Coords> {
		const size_t operator()(const Coords& c) const
		{
			return std::hash<int64_t>()(c.x) ^ std::hash<int64_t>()(c.y);
		}
	};
}