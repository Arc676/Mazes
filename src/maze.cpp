#include "maze.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include "Generators/generators.h"
#include "src/render.h"

Maze::Maze(unsigned w, unsigned h)
	: maze(w, h) {
	Generators::randomMaze(maze);
}

void Maze::render(SDL_Renderer* const renderer, const TileSettings& ts) const {
	setRenderColor(renderer, color);

	const int tileSize = (int)ts.tileSize;
	const int pathSize = (int)ts.getHallwayWidth();
	const int wallSize = (int)ts.wallThickness;

	for (int y = 0; y < maze.getHeight(); y++) {
		for (int x = 0; x < maze.getWidth(); x++) {
			auto tile = maze.at(x, y);
			if ((tile & Mazes::RIGHT_WALL) != 0) {
				SDL_Rect wall{x * tileSize + pathSize, y * tileSize, wallSize,
				              tileSize};
				SDL_RenderFillRect(renderer, &wall);
			}
			if ((tile & Mazes::BOTTOM_WALL) != 0) {
				SDL_Rect wall{x * tileSize, y * tileSize + pathSize, tileSize,
				              wallSize};
				SDL_RenderFillRect(renderer, &wall);
			}
		}
	}
}

bool Maze::resizeMaze(const unsigned w, const unsigned h) {
	if (w != maze.getWidth() || h != maze.getHeight()) {
		maze.resize(w, h);
		return true;
	}
	return false;
}
