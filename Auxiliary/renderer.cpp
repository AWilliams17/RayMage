//
// Created by awilliams on 7/27/18.
//

#include "renderer.h"

Renderer::Renderer() {
    this->window = new SDL_Window;
    this->renderer = new SDL_Renderer;
}

int Renderer::init(const int WIDTH, const int HEIGHT, const bool FULL_SCREEN, const string WINDOW_TITLE) {

}

int Renderer::terminate() {

}

int Renderer::clearScreen() {

}

int Renderer::redraw() {

}

int Renderer::drawLine(int x1, int y1, int x2, int y2) {

}

int Renderer::drawLineHorizontal(int y, int x1, int x2) {

}

int Renderer::drawLineVertical(int x, int y1, int y2) {

}