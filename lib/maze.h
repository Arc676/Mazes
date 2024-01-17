#ifndef LIB_MAZE_H
#define LIB_MAZE_H

#include <vector>

namespace Mazes {
	using Tile                 = unsigned char;
	constexpr Tile EMPTY       = 0;
	constexpr Tile RIGHT_WALL  = 1U << 0U;
	constexpr Tile BOTTOM_WALL = 1U << 1U;
	constexpr Tile BOTH_WALLS  = RIGHT_WALL | BOTTOM_WALL;
	constexpr Tile VISITED     = 1U << 2U;

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
