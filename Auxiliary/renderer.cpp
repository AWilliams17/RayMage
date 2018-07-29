//
// Created by awilliams on 7/27/18.
//

#include <SDL_video.h>
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
    SDL_WindowFlags window_setting = SDL_WINDOW_SHOWN;
    this->windowWidth = WIDTH;
    this->windowHeight = HEIGHT;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLException("Failed to initialize the video subsystem.");
    }
    this->window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, window_setting);
    if (this->window == nullptr) {
        throw SDLException("Failed to create window.");
    }
    if (FULL_SCREEN) {
        SDL_DisplayMode dm;
        SDL_GetDesktopDisplayMode(0, &dm);

        this->windowHeight = dm.h;
        this->windowWidth = dm.w;

        SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr) {
        throw SDLException("Failed to create renderer.");
    }
    TTF_Init();
    this->font = TTF_OpenFont("../Gameplay.ttf", 15);
}

void Renderer::terminate() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_CloseFont(this->font);
    SDL_Quit();
    TTF_Quit();
}

void Renderer::clearScreen() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
}

void Renderer::redraw() {
    SDL_RenderPresent(this->renderer);
}

//ToDo: More shapes
void Renderer::drawLine(const int X1, const int Y1, const int X2, const int Y2, const Color_RGBA COLOR) {
    SDL_SetRenderDrawColor(this->renderer, COLOR.R, COLOR.G, COLOR.B, COLOR.A);
    SDL_RenderDrawLine(this->renderer, X1, Y1, X2, Y2);
}

void Renderer::drawLineHorizontal(const int Y, const int X1, const int X2, const Color_RGBA COLOR) {
    SDL_SetRenderDrawColor(this->renderer, COLOR.R, COLOR.G, COLOR.B, COLOR.A);
    SDL_RenderDrawLine(this->renderer, X1, Y, X2, Y);
}

void Renderer::drawLineVertical(const int X, const int Y1, const int Y2, const Color_RGBA COLOR) {
    SDL_SetRenderDrawColor(this->renderer, COLOR.R, COLOR.G, COLOR.B, COLOR.A);
    SDL_RenderDrawLine(this->renderer, X, Y1, X, Y2);
}

void Renderer::drawText(const string TEXT, int TEXT_W, int TEXT_H,
                        int const TEXT_X, const int TEXT_Y, const Color_RGBA COLOR) {

    SDL_Color sdlColor = {COLOR.R, COLOR.G, COLOR.B, COLOR.A};

    SDL_Surface *textSurface = TTF_RenderText_Solid(this->font, TEXT.c_str(), sdlColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
    SDL_QueryTexture(textTexture, NULL, NULL, &TEXT_W, &TEXT_H);
    SDL_Rect dstrect = {TEXT_X, TEXT_Y, TEXT_W, TEXT_H };

    SDL_RenderCopy(this->renderer, textTexture, NULL, &dstrect);
    //SDL_RenderPresent(this->renderer);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void Renderer::drawRect(const SDL_Rect RECTANGLE_STRUCT, const Color_RGBA COLOR) {
    SDL_SetRenderDrawColor(this->renderer, COLOR.R, COLOR.G, COLOR.B, COLOR.A);
    SDL_RenderFillRect(this->renderer, &RECTANGLE_STRUCT);
}