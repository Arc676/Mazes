#include "settings.h"

#include <SDL_events.h>
#include <SDL_scancode.h>
#include <SDL_video.h>

#include <algorithm>
#include <cstdio>

#include "Generators/generators.h"
#include "imgui.h"
#include "maze.h"
#include "player.h"

void TileSettings::setSize(const unsigned size, const float wall) {
	tileSize      = size;
	wallRatio     = wall;
	wallThickness = (unsigned)(wall * (float)size);
}

unsigned TileSettings::getHallwayWidth() const {
	return tileSize - wallThickness;
}

GameSettings::GameSettings(const unsigned w, const unsigned h,
                           SDL_Window* const window, const float ratio,
                           Player& player, Maze& maze)
	: mazeWidth(w)
	, mazeHeight(h)
	, player(&player)
	, maze(&maze) {
	updateTileSize(window, ratio);
}

void GameSettings::updateTileSize(SDL_Window* const window, const float ratio) {
	if (window != nullptr) {
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	}

	unsigned tileSize =
		std::min(windowWidth / mazeWidth, windowHeight / mazeHeight);
	ts.setSize(tileSize, ratio);
}

void GameSettings::processEvent(const SDL_Event* const event) {
	switch (event->type) {
		case SDL_KEYUP:
			switch (event->key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					showSettings = !showSettings;
					break;
				case SDL_SCANCODE_GRAVE:
					showStats = !showStats;
					break;
				case SDL_SCANCODE_LALT:
					showMenuBar = !showMenuBar;
					break;
				case SDL_SCANCODE_SPACE:
					if (player->x == maze->getMaze().getWidth() - 1
					    && player->y == maze->getMaze().getHeight() - 1) {
						flags |= MAZE_REGEN;
					}
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
	if (ImGui::BeginMenu("Player")) {
		ImGui::MenuItem("Show path", nullptr, &player->showPath);
		ImGui::MenuItem("Show backtracking", nullptr, &player->showBacktrack);
		ImGui::MenuItem("Show statistics", nullptr, &showStats);
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}

void GameSettings::saveColors() {
	FILE* file = fopen(colorFilename.data(), "wb");
	if (file != nullptr) {
		fwrite(maze->color.data(), sizeof(float), 4, file);
		fwrite(player->playerColor.data(), sizeof(float), 4, file);
		fwrite(player->pathColor.data(), sizeof(float), 4, file);
		fclose(file);
		colorIO = "Saved color scheme to file";
	} else {
		colorIO = "Failed to open file for writing";
	}
}

void GameSettings::readColors() {
	FILE* file = fopen(colorFilename.data(), "rb");
	if (file != nullptr) {
		fread(maze->color.data(), sizeof(float), 4, file);
		fread(player->playerColor.data(), sizeof(float), 4, file);
		fread(player->pathColor.data(), sizeof(float), 4, file);
		fclose(file);
		colorIO = "Restored color scheme from file";
	} else {
		colorIO = "Failed to open file for reading";
	}
}

void GameSettings::colorSelect() {
	if (ImGui::TreeNode("Maze Colors")) {
		ImGui::ColorPicker3("Maze Walls", maze->color.data());
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Player Colors")) {
		ImGui::ColorPicker3("Player Color", player->playerColor.data());
		ImGui::ColorPicker3("Path Color", player->pathColor.data());
		ImGui::ColorPicker3("Backtracking Color",
		                    player->backtrackColor.data());
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Save/Restore Color Scheme")) {
		ImGui::InputText("Filename", colorFilename.data(), FILENAME_BUFLEN);
		if (ImGui::Button("Save")) {
			saveColors();
		}
		ImGui::SameLine();
		if (ImGui::Button("Restore")) {
			readColors();
		}
		if (colorIO != nullptr) {
			ImGui::Text("%s", colorIO);
		}
		ImGui::TreePop();
	}
}

void GameSettings::renderStats() const {
	ImGui::Text("Maze generator: %s", Generators::algoToString(lastUsed));

	const unsigned w     = maze->getMaze().getWidth();
	const unsigned h     = maze->getMaze().getHeight();
	const unsigned tiles = w * h;
	ImGui::Text("Maze size: %ux%u (%u tiles)", w, h, tiles);

	static constexpr double TO_PERCENT = 100;

	const unsigned walked = player->path.size();
	ImGui::Text("Path length: %u (%.02f%% of total)", walked,
	            (double)walked / tiles * TO_PERCENT);
	ImGui::Text("Backtracked: %zu tiles", player->backtracked.size());
}

void GameSettings::renderSettings() {
	if (ImGui::CollapsingHeader("Colors")) {
		colorSelect();
	}
	if (ImGui::CollapsingHeader("Traces")) {
		ImGui::Checkbox("Show Path", &player->showPath);
		ImGui::Checkbox("Show Backtracking", &player->showBacktrack);
	}
	if (ImGui::CollapsingHeader("Maze Size")) {
		ImGui::InputScalar("Maze Width", ImGuiDataType_U32, &mazeWidth);
		ImGui::InputScalar("Maze Height", ImGuiDataType_U32, &mazeHeight);
	}
	if (ImGui::CollapsingHeader("Maze Generation")) {
		mazeGenSelect();
	}
}

void GameSettings::render() {
	menuBar();

	if (showSettings) {
		if (ImGui::Begin("Settings")) {
			renderSettings();
		}
		ImGui::End();
	}

	if (showStats) {
		if (ImGui::Begin("Statistics", &showStats)) {
			renderStats();
		}
		ImGui::End();
	}
}

void GameSettings::mazeGenSelect() {
	if (ImGui::BeginCombo("Maze Generation Algorithm",
	                      Generators::algoToString(algo))) {
		for (int a = Generators::RANDOM_MAZE; a < Generators::ALGO_MAX; a++) {
			bool selected = a == algo;
			if (ImGui::Selectable(
					Generators::algoToString((Generators::GeneratorAlgo)a),
					selected)) {
				algo = (Generators::GeneratorAlgo)a;
			}
			if (selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	switch (algo) {
		case Generators::RECURSIVE_DIVISION:
			ImGui::InputScalar("Minimum chamber size", ImGuiDataType_U32,
			                   &minChamberSize);
			break;
		default:
			break;
	}
	if (ImGui::Button("Regenerate Maze")) {
		flags |= MAZE_REGEN;
	}
}

void GameSettings::generateMaze() {
	updateTileSize(nullptr, ts.wallRatio);
	maze->resizeMaze(mazeWidth, mazeHeight);
	lastUsed = algo;
	switch (algo) {
		case Generators::RANDOM_MAZE:
			maze->regenMaze(&Generators::randomMaze);
			break;
		case Generators::RECURSIVE_DIVISION:
			maze->regenMaze(&Generators::recursiveDivision, minChamberSize);
			break;
		case Generators::RANDOM_DFS:
			maze->regenMaze(&Generators::randomDFS);
			break;
		default:
			break;
	}
}
