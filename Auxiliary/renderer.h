//
// Created by awilliams on 7/27/18.
//

#ifndef RAYMAGE_RENDERER_H
#define RAYMAGE_RENDERER_H

#include "SDL.h"
#include "iostream"
#include <string>

using namespace std;

namespace renderer {
    string init(SDL_Window *window, SDL_Renderer *renderer, const int WIDTH, const int HEIGHT, const bool FULL_SCREEN, const string WINDOW_TITLE);
    void terminate(SDL_Window *window, SDL_Renderer *renderer);
    void clear_screen(SDL_Renderer *renderer);
    void redraw(SDL_Renderer *renderer);
}

#endif //RAYMAGE_RENDERER_H
