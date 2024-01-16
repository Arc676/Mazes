#include "maze.h"

#include <SDL_rect.h>
#include <SDL_render.h>

#include "Generators/generators.h"

Maze::Maze(unsigned w, unsigned h)
	: maze(w, h) {
	Generators::randomMaze(maze);
}

void Maze::render(SDL_Renderer* const renderer, const unsigned tileSize) const {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int y = 0; y < maze.getHeight(); y++) {
		for (int x = 0; x < maze.getWidth(); x++) {
			auto tile = maze.at(x, y);
			if ((tile & Mazes::RIGHT_WALL) != 0) {
				SDL_Rect wall{x * 100 + 90, y * 100, 10, 100};
				SDL_RenderFillRect(renderer, &wall);
			}
			if ((tile & Mazes::BOTTOM_WALL) != 0) {
				SDL_Rect wall{x * 100, y * 100 + 90, 100, 10};
				SDL_RenderFillRect(renderer, &wall);
			}
		}
	}
}
