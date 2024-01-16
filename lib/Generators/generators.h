#ifndef LIB_MAZE_GENERATORS_H
#define LIB_MAZE_GENERATORS_H

#include <SDL2/SDL_rect.h>

#include "maze.h"

namespace Generators {
	enum GeneratorAlgo {
		RANDOM_MAZE,
		RECURSIVE_DIVISION,
	};

	void randomMaze(Mazes::Maze& maze);

	void recursiveDivision(Mazes::Maze& maze, int minSize);
}  // namespace Generators

#endif
