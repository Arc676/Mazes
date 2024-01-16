#include "player.h"

#include <SDL2/SDL_render.h>
#include <SDL_rect.h>

void Player::render(SDL_Renderer* const renderer,
                    const TileSettings& ts) const {
	const int size = (int)ts.getHallwayWidth();
	SDL_Rect rect{x, y, size, size};
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
