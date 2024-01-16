#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#include "maze.h"
#include "src/settings.h"

class Player {
	int x = 0;
	int y = 0;

public:
	void render(SDL_Renderer* renderer, const TileSettings& ts) const;

	void processEvent(const SDL_Event* event, const Mazes::Maze& maze);
};

#endif
