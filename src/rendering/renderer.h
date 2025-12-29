#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

// Basic rendering utilities
void renderer_draw_grid(SDL_Renderer* renderer, int width, int height, int spacing);
void renderer_draw_circle(SDL_Renderer* renderer, int x, int y, int radius);
void renderer_draw_line_dashed(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int dash_length);
void renderer_draw_arrow(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int head_size);

// Text rendering (requires SDL_ttf)
void renderer_draw_text(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color);

#endif // RENDERER_H
