#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SDL2/SDL_render.h>

#include <array>

void setRenderColor(SDL_Renderer* renderer, const std::array<float, 4>& color);

#endif
