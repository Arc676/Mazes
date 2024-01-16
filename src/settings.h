#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL2/SDL_video.h>
#include <SDL_events.h>

#include <array>

struct TileSettings {
	unsigned tileSize;
	unsigned wallThickness;
	float wallRatio;

	TileSettings() = default;

	void setSize(unsigned size, float wall);

	[[nodiscard]] unsigned getHallwayWidth() const;
};

class GameSettings {
	// game settings
	unsigned mazeWidth;
	unsigned mazeHeight;
	TileSettings ts{};

	// render settings
	std::array<float, 3> playerColor{0, 1, 0};
	std::array<float, 3> mazeColor{1, 1, 1};

	// UI state
	bool showSettings = false;
	bool showMenuBar  = false;

public:
	using Flag = unsigned;

	constexpr static Flag QUIT_PRESSED   = 1U << 0U;
	constexpr static Flag COLORS_CHANGED = 1U << 1U;

private:
	Flag flags = 0;

	void menuBar();

public:
	GameSettings(unsigned w, unsigned h, SDL_Window* window, float ratio);

	[[nodiscard]] const TileSettings& getTileSettings() const { return ts; }

	[[nodiscard]] unsigned getWidth() const { return mazeWidth; }

	[[nodiscard]] unsigned getHeight() const { return mazeHeight; }

	[[nodiscard]] Flag getFlags() const { return flags; }

	void processEvent(const SDL_Event* event);

	void render();
};

#endif
