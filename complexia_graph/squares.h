#ifndef SQUARES_H
#define SQUARES_H

#include "../backend.h"
#include <SDL2/SDL_render.h>

typedef struct Line {
    float x0, y0, x1, y1;
} Line;

float eval_at(Bytecode bc, Complex pos);
void render(Bytecode bc, float square_size, SDL_Renderer *renderer);

#endif