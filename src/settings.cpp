#include "settings.h"

#include <SDL_video.h>

#include <algorithm>

void TileSettings::setSize(const unsigned size, const float wall) {
	tileSize      = size;
	wallRatio     = wall;
	wallThickness = (unsigned)(wall * (float)size);
}

unsigned TileSettings::getHallwayWidth() const {
	return tileSize - wallThickness;
}

GameSettings::GameSettings(const unsigned w, const unsigned h,
                           SDL_Window* const window, const float ratio)
	: mazeWidth(w)
	, mazeHeight(h)
	, ts() {
	int width  = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);

	unsigned tileSize = std::min(width / w, height / h);
	ts.setSize(tileSize, ratio);
}
