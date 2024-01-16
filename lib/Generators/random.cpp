#include <random>

#include "Generators/generators.h"
#include "maze.h"

void Generators::randomMaze(Mazes::Maze& maze) {
	constexpr int RANGE_MIN = 1;
	constexpr int RANGE_MAX = 100;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(RANGE_MIN, RANGE_MAX);
	auto rand = [&]() {
		return dist(gen) % 2 == 0;
	};

	for (int y = 0; y < maze.getHeight(); y++) {
		for (int x = 0; x < maze.getWidth(); x++) {
			unsigned tile = Mazes::EMPTY;
			if (rand()) {
				tile |= Mazes::RIGHT_WALL;
			}
			if (rand()) {
				tile |= Mazes::BOTTOM_WALL;
			}
			maze.at(x, y) = (Mazes::Tile)tile;
		}
	}
}
