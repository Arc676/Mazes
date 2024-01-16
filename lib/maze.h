#ifndef LIB_MAZE_H
#define LIB_MAZE_H

#include <vector>

namespace Mazes {
	using Tile                 = unsigned;
	constexpr Tile EMPTY       = 0U;
	constexpr Tile RIGHT_WALL  = 0b01U;
	constexpr Tile BOTTOM_WALL = 0b10U;
	constexpr Tile BOTH_WALLS  = 0b11U;

	class Maze {
		using Vec = std::vector<Tile>;

		unsigned width;
		unsigned height;
		Vec tiles;

		void alloc();

	public:
		Maze(unsigned w, unsigned h);

		void clear(bool walls = false);

		void resize(unsigned w, unsigned h);

		[[nodiscard]] Tile at(unsigned x, unsigned y) const;

		[[nodiscard]] Tile& at(unsigned x, unsigned y);

		[[nodiscard]] unsigned getWidth() const { return width; }

		[[nodiscard]] unsigned getHeight() const { return height; }
	};
}  // namespace Mazes

#endif
