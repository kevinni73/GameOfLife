#include "Grid.h"
#include <iostream>

namespace {
	constexpr uint64_t kMax = std::numeric_limits<int64_t>::max();
	constexpr uint64_t kMin = std::numeric_limits<int64_t>::min();
}

void Grid::SetAlive(int64_t x, int64_t y) {
	SetAlive(x, y, _alive, _neighbors);
}

void Grid::SetAlive(int64_t x, int64_t y, std::unordered_set<Coords>& alive, std::unordered_map<Coords, unsigned char>& neighbors) {
	alive.emplace(x, y);
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i == 0 && j == 0) ||
				(i == -1 && x == kMin) || (i == 1 && x == kMax) ||
				(j == -1 && y == kMin) || (j == 1 && y == kMax)) {
				continue;
			}

			neighbors[{x + i, y + j}]++;
		}
	}
}

void Grid::SimulateStep() {
	std::unordered_set<Coords> aliveNext;
	std::unordered_map<Coords, unsigned char> neighborsNext;

	for (const auto& neighborInfo : _neighbors) {
		if (neighborInfo.second == 3 || (_alive.find(neighborInfo.first) != _alive.end() && neighborInfo.second == 2)) {
			SetAlive(neighborInfo.first.x, neighborInfo.first.y, aliveNext, neighborsNext);
		}
	}

	_alive = std::move(aliveNext);
	_neighbors = std::move(neighborsNext);
}

// Print from (-halfNum, -halfNum) to (halfNum, halfNum)
void Grid::Display(int halfNum) {
	int totalSize = halfNum * 2 + 3;
	std::string horizontalBorder(totalSize, '-');
	std::string line(totalSize, '|');
	std::cout << horizontalBorder << std::endl;
	for (int y = halfNum; y >= -halfNum; y--) {
		for (int x = -halfNum; x <= halfNum; x++) {
			if (_alive.find({ x, y }) != _alive.end()) {
				line[x + halfNum + 1] = 'x';
			}
			else {
				line[x + halfNum + 1] = ' ';
			}
		}
		std::cout << line << std::endl;
	}
	std::cout << horizontalBorder << std::endl;
}

void Grid::Print() {
	std::cout << "Alive coordinates: " << std::endl;
	for (const auto& coord : _alive) {
		std::cout << coord.x << ", " << coord.y << std::endl;
	}
	std::cout << std::endl << "Neighbor counts: " << std::endl;
	for (const auto& neighbor : _neighbors) {
		std::cout << neighbor.first.x << ", " << neighbor.first.y << ": "
			<< static_cast<int>(neighbor.second) << std::endl;
	}
}