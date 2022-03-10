#include "Grid.h"
#include <iostream>
#include <string>
#include <sstream>

namespace {
	constexpr unsigned int kHalfGridSize = 20;
}

bool ParseInput(Grid& grid) {
	int64_t x, y;
	std::string input;
	while (std::getline(std::cin, input)) {
		if (input.empty() || input[0] == '-') {
			break;
		}

		std::istringstream stream(input);
		if (stream.get() == '(' && stream >> x && stream.get() == ',' && stream >> y) {
			grid.SetAlive(x, y);
		}
		else {
			std::cout << "Failed to parse input: " << input << std::endl;
			return false;
		}
	}

	return true;
}

void RunSimulation(Grid& grid) {
	std::string input;
	while (true) {
		grid.Display(kHalfGridSize);

		std::cout << "Press ENTER to continue or enter q to quit: ";
		std::getline(std::cin, input);
		if (input == "q" || input == "Q") {
			return;
		}

		grid.SimulateStep();
	}
}

int main()
{
	Grid grid;
	if (!ParseInput(grid)) {
		return -1;
	}
	RunSimulation(grid);
	return 0;
}