#include <SDL2/SDL.h>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "maze.h"
#include "player.h"
#include "src/settings.h"

void initializeUI(SDL_Window* const window, SDL_Renderer* const renderer) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	// NOLINTNEXTLINE(hicpp-signed-bitwise)
	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);
}

void newFrame() {
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError()
				  << std::endl;
		return 1;
	}

	constexpr int FRAME_DELAY   = 1000 / 60;
	constexpr int WINDOW_WIDTH  = 1000;
	constexpr int WINDOW_HEIGHT = 1000;

	unsigned winFlags = 0;

	SDL_Window* win = SDL_CreateWindow("Mazes", SDL_WINDOWPOS_CENTERED,
	                                   SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
	                                   WINDOW_HEIGHT, winFlags);

	unsigned flags         = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, flags);
	initializeUI(win, renderer);

	constexpr unsigned DEFAULT_MAZE_SIZE = 10;
	constexpr float DEFAULT_WALL_RATIO   = 0.1;

	GameSettings settings{DEFAULT_MAZE_SIZE, DEFAULT_MAZE_SIZE, win,
	                      DEFAULT_WALL_RATIO};

	Maze maze(settings);
	Player player;

	while (true) {
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			player.processEvent(&event, maze.getMaze());
		}

		newFrame();
		// TODO: draw UI
		ImGui::Render();

		// NOLINTNEXTLINE(*-magic-numbers)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		maze.render(renderer, settings.ts);
		player.render(renderer, settings.ts);

		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);
		SDL_Delay(FRAME_DELAY);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
