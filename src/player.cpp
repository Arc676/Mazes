#include "player.h"

#include <SDL2/SDL_render.h>
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_scancode.h>

#include "maze.h"

void Player::render(SDL_Renderer* const renderer,
                    const TileSettings& ts) const {
	const int tileSize = (int)ts.tileSize;
	const int size     = (int)ts.getHallwayWidth();
	SDL_Rect rect{x * tileSize, y * tileSize, size, size};
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
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
					}
					break;
				case SDL_SCANCODE_A:
					if (x > 0 && (maze.at(x - 1, y) & Mazes::RIGHT_WALL) == 0) {
						x--;
					}
					break;
				case SDL_SCANCODE_S:
					if (y < maze.getHeight() - 1
					    && (maze.at(x, y) & Mazes::BOTTOM_WALL) == 0) {
						y++;
					}
					break;
				case SDL_SCANCODE_D:
					if (x < maze.getWidth() - 1
					    && (maze.at(x, y) & Mazes::RIGHT_WALL) == 0) {
						x++;
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
