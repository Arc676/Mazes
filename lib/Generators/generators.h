#ifndef LIB_MAZE_GENERATORS_H
#define LIB_MAZE_GENERATORS_H

#include <SDL2/SDL_rect.h>

#include "maze.h"

namespace Generators {
	void randomMaze(Mazes::Maze& maze);

	void recursiveDivision(Mazes::Maze& maze, int minSize = 2,
	                       const SDL_Rect& bounds = {0, 0, -1, -1});
}  // namespace Generators

#endif
