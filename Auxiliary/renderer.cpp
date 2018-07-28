//
// Created by awilliams on 7/27/18.
//

#include "renderer.h"
Color_RGBA::Color_RGBA(const Uint8 R, const Uint8 G, const Uint8 B, const Uint8 A) {
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = A;
}

SDLException::SDLException(const std::string& operation_desc)
        : m_msg(std::string("Error occurred during operation: ") + operation_desc + " SDLError(): " + SDL_GetError()) {}

const char* SDLException::what() const throw(){
    return m_msg.c_str();
}

Renderer::Renderer(const string WINDOW_TITLE, const int WIDTH, const int HEIGHT, const bool FULL_SCREEN) {
    this->windowWidth = WIDTH;
    this->windowHeight = HEIGHT;
    SDL_WindowFlags window_setting = SDL_WINDOW_SHOWN;

    if (FULL_SCREEN) {
        window_setting = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLException("Failed to initialize the video subsystem.");
    }
    this->window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, window_setting);
    if (this->window == nullptr) {
        throw SDLException("Failed to create window.");
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr) {
        throw SDLException("Failed to create renderer.");
    }
}

int Renderer::terminate() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

int Renderer::clearScreen() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
}

int Renderer::redraw() {
    SDL_RenderPresent(this->renderer);
}

int Renderer::drawLine(const int X1, const int Y1, const int X2, const int Y2, Color_RGBA color) {
    SDL_SetRenderDrawColor(this->renderer, color.R, color.G, color.B, color.A);
    SDL_RenderDrawLine(this->renderer, X1, Y1, X2, Y2);
}

int Renderer::drawLineHorizontal(int Y, int X1, int X2, Color_RGBA color) {
    SDL_SetRenderDrawColor(this->renderer, color.R, color.G, color.B, color.A);
    SDL_RenderDrawLine(this->renderer, X1, Y, X2, Y);
}

int Renderer::drawLineVertical(int X, int Y1, int Y2, Color_RGBA color) {
    SDL_SetRenderDrawColor(this->renderer, color.R, color.G, color.B, color.A);
    SDL_RenderDrawLine(this->renderer, X, Y1, X, Y2);
}