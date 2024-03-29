#ifndef LIB_MAZE_GENERATORS_H
#define LIB_MAZE_GENERATORS_H

#include <SDL2/SDL_rect.h>

#include "maze.h"

namespace Generators {
	enum GeneratorAlgo {
		RANDOM_MAZE,
		RECURSIVE_DIVISION,
		RANDOM_DFS,
		ALGO_MAX,
	};

	const char* algoToString(GeneratorAlgo algo);

	void randomMaze(Mazes::Maze& maze);

	void recursiveDivision(Mazes::Maze& maze, int minSize = 1);

	void randomDFS(Mazes::Maze& maze);
}  // namespace Generators

#endif
