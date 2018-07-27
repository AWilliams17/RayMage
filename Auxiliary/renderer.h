//
// Created by awilliams on 7/27/18.
//

#ifndef RAYMAGE_RENDERER_H
#define RAYMAGE_RENDERER_H

#include "SDL.h"
#include "iostream"
#include <string>

typedef std::string string;

namespace rendering_auxiliary {
    int init(SDL_Window *window, SDL_Renderer *renderer, const int WIDTH, const int HEIGHT, const bool FULL_SCREEN, const string WINDOW_TITLE);
    int terminate(SDL_Window *window, SDL_Renderer *renderer);
    int clear_screen(SDL_Renderer *renderer);
    int redraw(SDL_Renderer *renderer);
}

namespace rendering_2D {
    int drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
    int drawLineHorizontal(SDL_Renderer *renderer, int y, int x1, int x2);
    int drawLineVertical(SDL_Renderer *renderer, int x, int y1, int y2);
}

#endif //RAYMAGE_RENDERER_H
