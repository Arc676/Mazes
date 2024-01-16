#include "maze.h"

#include <algorithm>
#include <cstddef>

namespace Mazes {
	Maze::Maze(unsigned w, unsigned h)
		: width(w)
		, height(h) {
		alloc();
	}

	void Maze::alloc() {
		tiles.resize(static_cast<size_t>(width) * height);
	}

	void Maze::clear(const bool walls) {
		std::ranges::fill(tiles, walls ? BOTH_WALLS : EMPTY);
	}

	void Maze::resize(unsigned w, unsigned h) {
		width  = w;
		height = h;
		alloc();
	}

	Tile& Maze::at(unsigned x, unsigned y) {
		return tiles.at(y * width + x);
	}

	Tile Maze::at(unsigned x, unsigned y) const {
		return tiles.at(y * width + x);
	}
}  // namespace Mazes
