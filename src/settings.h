#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL2/SDL_video.h>
#include <SDL_events.h>

#include <array>

#include "Generators/generators.h"

class Maze;
class Player;

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
	int windowWidth  = 0;
	int windowHeight = 0;

	// game elements
	Player* player;
	Maze* maze;

	// UI state
	bool showSettings = false;
	bool showMenuBar  = false;
	bool showStats    = false;

	// maze generation
	Generators::GeneratorAlgo algo     = Generators::RECURSIVE_DIVISION;
	Generators::GeneratorAlgo lastUsed = Generators::RECURSIVE_DIVISION;
	unsigned minChamberSize            = 1;

	void updateTileSize(SDL_Window* window, float ratio);

public:
	using Flag = unsigned;

	constexpr static Flag QUIT_PRESSED   = 1U << 0U;
	constexpr static Flag COLORS_CHANGED = 1U << 1U;
	constexpr static Flag MAZE_REGEN     = 1U << 2U;

private:
	Flag flags = 0;

	void menuBar();

	void mazeGenSelect();

	void colorSelect();

	void renderStats() const;

	void renderSettings();

public:
	GameSettings(unsigned w, unsigned h, SDL_Window* window, float ratio,
	             Player& player, Maze& maze);

	[[nodiscard]] const TileSettings& getTileSettings() const { return ts; }

	[[nodiscard]] unsigned getWidth() const { return mazeWidth; }

	[[nodiscard]] unsigned getHeight() const { return mazeHeight; }

	[[nodiscard]] Flag getFlags() const { return flags; }

	void resetFlags() { flags = 0; }

	void generateMaze();

	void processEvent(const SDL_Event* event);

	void render();
};

#endif
