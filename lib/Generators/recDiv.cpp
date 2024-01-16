#include <SDL2/SDL_rect.h>

#include <cassert>
#include <random>

#include "Generators/generators.h"
#include "maze.h"

// NOLINTNEXTLINE(*recursion)
void Generators::recursiveDivision(Mazes::Maze& maze, const int minSize,
                                   const SDL_Rect& bounds) {
	static std::random_device rd;
	static std::mt19937 gen(rd());

	static std::uniform_real_distribution<> randPos(0, 1);
	// returns a random number in the half-open interval [a, b)
	static auto rand = [&](unsigned a, unsigned b) -> int {
		assert(b > a);
		return (int)(randPos(gen) * (b - a) + a);
	};

	static std::uniform_int_distribution<> randOpen(1, 4);
	enum Opening {
		NORTH = 1,
		EAST  = 2,
		SOUTH = 3,
		WEST  = 4,
	};

	if (bounds.w < 0) {
		maze.clear();
	}

	// upper left corner of chamber
	const int x0 = bounds.x;
	const int y0 = bounds.y;

	// lower right corner of chamber
	const int x1 = bounds.w < 0 ? (int)maze.getWidth() : bounds.w;
	if (x1 - x0 <= minSize) {
		return;
	}

	const int y1 = bounds.h < 0 ? (int)maze.getHeight() : bounds.h;
	if (y1 - y0 <= minSize) {
		return;
	}

	const int wallX = rand(x0, x1 - 1);
	const int wallY = rand(y0, y1 - 1);

	for (int x = x0; x < x1; x++) {
		maze.at(x, wallY) |= Mazes::BOTTOM_WALL;
	}
	for (int y = y0; y < y1; y++) {
		maze.at(wallX, y) |= Mazes::RIGHT_WALL;
	}

	// NOLINTBEGIN(*bitwise)
	const auto closed = (Opening)randOpen(gen);
	if (closed != NORTH) {
		const int gap = rand(y0, wallY + 1);
		maze.at(wallX, gap) &= ~Mazes::RIGHT_WALL;
	}
	if (closed != SOUTH) {
		const int gap = rand(wallY + 1, y1);
		maze.at(wallX, gap) &= ~Mazes::RIGHT_WALL;
	}
	if (closed != EAST) {
		const int gap = rand(wallX + 1, x1);
		maze.at(gap, wallY) &= ~Mazes::BOTTOM_WALL;
	}
	if (closed != WEST) {
		const int gap = rand(x0, wallX + 1);
		maze.at(gap, wallY) &= ~Mazes::BOTTOM_WALL;
	}
	// NOLINTEND(*bitwise)

	SDL_Rect nw{x0, y0, wallX, wallY};
	recursiveDivision(maze, minSize, nw);

	SDL_Rect ne{wallX, y0, x1, wallY};
	recursiveDivision(maze, minSize, ne);

	SDL_Rect sw{x0, wallY, wallX, y1};
	recursiveDivision(maze, minSize, sw);

	SDL_Rect se{wallX, wallY, x1, y1};
	recursiveDivision(maze, minSize, se);
}
