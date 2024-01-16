#include "settings.h"

#include <SDL_events.h>
#include <SDL_scancode.h>
#include <SDL_video.h>

#include <algorithm>

#include "imgui.h"
#include "maze.h"

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
	, mazeHeight(h) {
	int width  = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);

	unsigned tileSize = std::min(width / w, height / h);
	ts.setSize(tileSize, ratio);
}

void GameSettings::processEvent(const SDL_Event* const event) {
	switch (event->type) {
		case SDL_KEYUP:
			switch (event->key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					showSettings = !showSettings;
					break;
				case SDL_SCANCODE_LALT:
					showMenuBar = !showMenuBar;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void GameSettings::menuBar() {
	if (!showMenuBar) {
		return;
	}

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Game")) {
		if (ImGui::MenuItem("Regenerate Maze")) {
			flags |= MAZE_REGEN;
		}
		if (ImGui::MenuItem("Quit")) {
			flags |= QUIT_PRESSED;
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}

void GameSettings::render() {
	flags = 0;
	menuBar();

	if (!showSettings) {
		return;
	}

	if (ImGui::Begin("Settings")) {
		if (ImGui::CollapsingHeader("Colors")) {
			if (ImGui::ColorPicker3("Player Color", playerColor.data())) {
				flags |= COLORS_CHANGED;
			}
			if (ImGui::ColorPicker3("Maze Color", mazeColor.data())) {
				flags |= COLORS_CHANGED;
			}
		}
	}
	ImGui::End();
}

void GameSettings::generateMaze(Maze& maze) const {
	switch (algo) {
		case Generators::RANDOM_MAZE:
			maze.regenMaze(&Generators::randomMaze);
			break;
		case Generators::RECURSIVE_DIVISION:
			maze.regenMaze(&Generators::recursiveDivision, minChamberSize);
			break;
	}
}
