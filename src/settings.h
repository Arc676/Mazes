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

class GameSettings {
	unsigned mazeWidth;
	unsigned mazeHeight;
	TileSettings ts;

public:
	GameSettings(unsigned w, unsigned h, SDL_Window* window, float ratio);

	[[nodiscard]] const TileSettings& getTileSettings() const { return ts; }

	[[nodiscard]] unsigned getWidth() const { return mazeWidth; }

	[[nodiscard]] unsigned getHeight() const { return mazeHeight; }
};

#endif
