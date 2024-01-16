#include "player.h"

#include <SDL2/SDL_render.h>
#include <SDL_rect.h>

void Player::render(SDL_Renderer* const renderer,
                    const unsigned tileSize) const {
	SDL_Rect rect{x, y, 90, 90};
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
