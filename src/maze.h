#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL_render.h>

#include "lib/maze.h"
#include "src/settings.h"

class Maze {
	Mazes::Maze maze;

public:
	Maze(unsigned w, unsigned h);

	explicit Maze(const GameSettings& gs)
		: Maze(gs.mazeWidth, gs.mazeHeight) {}

	void render(SDL_Renderer* renderer, const TileSettings& ts) const;
};

#endif
