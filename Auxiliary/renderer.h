//
// Created by awilliams on 7/27/18.
//

#ifndef RAYMAGE_RENDERER_H
#define RAYMAGE_RENDERER_H

#include "SDL.h"
#include "SDL2/SDL_ttf.h"
#include "string"

typedef std::string string;

typedef struct Color_RGBA {
    Color_RGBA(const Uint8 R, const Uint8 G, const Uint8 B, const Uint8 A);
    Uint8 R, G, B, A;
};

typedef struct Colors {
    const Color_RGBA BLACK=     Color_RGBA(0, 0, 0, 255);
    const Color_RGBA RED=       Color_RGBA(255, 0, 0, 255);
    const Color_RGBA GREEN=     Color_RGBA(0, 255, 0, 255);
    const Color_RGBA BLUE=      Color_RGBA(0, 0, 255, 255);
    const Color_RGBA CYAN=      Color_RGBA(0, 255, 255, 255);
    const Color_RGBA MAGENTA=   Color_RGBA(255, 0, 255, 255);
    const Color_RGBA YELLOW=    Color_RGBA(255, 255, 0, 255);
    const Color_RGBA WHITE=     Color_RGBA(255, 255, 255, 255);
    const Color_RGBA GRAY=      Color_RGBA(128, 128, 128, 255);
    const Color_RGBA GREY=      Color_RGBA(192, 192, 192, 255);
    const Color_RGBA MAROON=    Color_RGBA(128, 0, 0, 255);
    const Color_RGBA DARKGREEN= Color_RGBA(0, 128, 0, 255);
    const Color_RGBA NAVY=      Color_RGBA(0, 0, 128, 255);
    const Color_RGBA TEAL=      Color_RGBA(0, 128, 128, 255);
    const Color_RGBA PURPLE=    Color_RGBA(128, 0, 128, 255);
    const Color_RGBA OLIVE=     Color_RGBA(128, 128, 0, 255);
};

class SDLException : public std::exception {
    string m_msg;
public:
    SDLException(const std::string& operation_desc);
    virtual const char* what() const throw();
};

class Renderer {
public:
    const Colors colors;
    Renderer(const string WINDOW_TITLE, const int WIDTH, const int HEIGHT, const bool FULL_SCREEN);
    void terminate();
    void clearScreen();
    void redraw();
    void drawLine(const int X1, const int Y1, const int X2, const int Y2, Color_RGBA color);
    void drawLineHorizontal(int Y, int X1, int X2, Color_RGBA color);
    void drawLineVertical(int X, int Y1, int Y2, Color_RGBA color);
    void drawText(const string TEXT, int TEXT_W, int TEXT_H, int const TEXT_X, const int TEXT_Y, const Color_RGBA color);
    void drawRect(const SDL_Rect RECTANGLE_STRUCT, const Color_RGBA COLOR);
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int windowWidth;
    int windowHeight;
};

#endif //RAYMAGE_RENDERER_H
