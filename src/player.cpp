#include "player.h"

#include <SDL2/SDL_render.h>
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_scancode.h>

#include "maze.h"
#include "src/render.h"

void Player::render(SDL_Renderer* const renderer,
                    const TileSettings& ts) const {
	const int tileSize = (int)ts.tileSize;
	const int size     = (int)ts.getHallwayWidth();

	auto renderPath = [&](const Path& path, const Color& color) {
		setRenderColor(renderer, color);
		SDL_Rect rect{0, 0, size, size};
		for (const auto& tile : path) {
			rect.x = tile.x * tileSize;
			rect.y = tile.y * tileSize;
			SDL_RenderFillRect(renderer, &rect);
		}
	};

	// show backtracked tiles
	if (showBacktrack) {
		renderPath(backtracked, backtrackColor);
	}

	// show path to current position
	if (showPath) {
		renderPath(path, pathColor);
	}

	// render player
	SDL_Rect rect{x * tileSize, y * tileSize, size, size};
	setRenderColor(renderer, playerColor);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::reset() {
	x = y = 0;
	path.clear();
	path.push_back({0, 0});
	backtracked.clear();
}

void Player::trackMove() {
	SDL_Point now{x, y};
	if (path.size() < 2) {
		path.push_back(now);
		return;
	}
	SDL_Point last   = path.back();
	SDL_Point before = path.at(path.size() - 2);
	if (now.x == before.x && now.y == before.y) {
		backtracked.push_back(last);
		path.pop_back();
	} else {
		path.push_back(now);
	}
}

void Player::processEvent(const SDL_Event* const event,
                          const Mazes::Maze& maze) {
	switch (event->type) {
		case SDL_KEYUP:
			switch (event->key.keysym.scancode) {
				case SDL_SCANCODE_W:
					if (y > 0
					    && (maze.at(x, y - 1) & Mazes::BOTTOM_WALL) == 0) {
						y--;
						trackMove();
					}
					break;
				case SDL_SCANCODE_A:
					if (x > 0 && (maze.at(x - 1, y) & Mazes::RIGHT_WALL) == 0) {
						x--;
						trackMove();
					}
					break;
				case SDL_SCANCODE_S:
					if (y < maze.getHeight() - 1
					    && (maze.at(x, y) & Mazes::BOTTOM_WALL) == 0) {
						y++;
						trackMove();
					}
					break;
				case SDL_SCANCODE_D:
					if (x < maze.getWidth() - 1
					    && (maze.at(x, y) & Mazes::RIGHT_WALL) == 0) {
						x++;
						trackMove();
					}
					break;
				case SDL_SCANCODE_R:
					reset();
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
