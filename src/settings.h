#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL2/SDL_video.h>

struct TileSettings {
	unsigned tileSize;
	unsigned wallThickness;
	float wallRatio;

	TileSettings() = default;

	void setSize(unsigned size, float wall);

	[[nodiscard]] unsigned getHallwayWidth() const;
};

struct GameSettings {
	unsigned mazeWidth;
	unsigned mazeHeight;
	TileSettings ts;

	GameSettings(unsigned w, unsigned h, SDL_Window* window, float ratio);
};

#endif
