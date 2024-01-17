#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL_render.h>
#include <SDL_pixels.h>

#include <functional>
#include <type_traits>

#include "lib/maze.h"
#include "src/settings.h"

template <typename Gen, typename... Args>
concept MazeGenerator =
	std::is_convertible_v<Gen, std::function<void(Mazes::Maze&, Args...)>>;

class Maze {
	Mazes::Maze maze;

	// NOLINTBEGIN(*magic-numbers)
	using Color = std::array<float, 4>;
	Color color{1, 1, 1, 1};
	// NOLINTEND(*magic-numbers)

public:
	Maze(unsigned w, unsigned h);

	explicit Maze(const GameSettings& gs)
		: Maze(gs.getWidth(), gs.getHeight()) {}

	void render(SDL_Renderer* renderer, const TileSettings& ts) const;

	[[nodiscard]] const Mazes::Maze& getMaze() const { return maze; }

	bool resizeMaze(unsigned w, unsigned h);

	template <typename MazeGen, typename... Args>
	void regenMaze(MazeGen generator, Args&&... args)
		requires MazeGenerator<MazeGen, Args...>
	{
		generator(maze, args...);
	}
};

#endif
