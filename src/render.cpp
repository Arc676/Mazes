#include "render.h"

#include <SDL2/SDL_render.h>

void setRenderColor(SDL_Renderer* const renderer,
                    const std::array<float, 4>& color) {
	// NOLINTBEGIN(*magic-numbers)
	SDL_SetRenderDrawColor(
		renderer, (Uint8)(color.at(0) * 255), (Uint8)(color.at(1) * 255),
		(Uint8)(color.at(2) * 255), (Uint8)(color.at(3) * 255));
	// NOLINTEND(*magic-numbers)
}
