//
// Created by awilliams on 7/27/18.
//

#include "renderer.h"

namespace rendering_auxiliary {
    int init(SDL_Window *window, SDL_Renderer *renderer,
                const int WIDTH, const int HEIGHT, const bool FULL_SCREEN, const string WINDOW_TITLE) {

    }

    int terminate(SDL_Window *window, SDL_Renderer *renderer) {

    }

    int clearScreen(SDL_Renderer *renderer) {

    }

    int redraw(SDL_Renderer *renderer) {

    }
}

namespace rendering_2D {
    int drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {

    }

    int drawLineHorizontal(SDL_Renderer *renderer, int y, int x1, int x2) {

    }

    int drawLineVertical(SDL_Renderer *renderer, int x, int y1, int y2) {

    }
}
