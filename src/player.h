#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL_pixels.h>

#include <array>

#include "maze.h"
#include "src/settings.h"

class Player {
	int x = 0;
	int y = 0;

	// NOLINTBEGIN(*magic-numbers)
	using Color = std::array<float, 4>;
	Color playerColor{0, 1, 0, 1};
	Color traceColor{0.5, 1, 0.5, 1};
	Color backtrackColor{1, 0.5, 0.5, 1};
	// NOLINTEND(*magic-numbers)

public:
	void render(SDL_Renderer* renderer, const TileSettings& ts) const;

	void processEvent(const SDL_Event* event, const Mazes::Maze& maze);

	void reset();
};

#endif
