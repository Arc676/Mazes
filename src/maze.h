#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL_render.h>

#include "lib/maze.h"

class Maze {
	Mazes::Maze maze;

public:
	Maze(unsigned w, unsigned h);

	void render(SDL_Renderer* renderer, unsigned tileSize) const;
};

#endif
