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
    Color_RGBA(Uint8 R, Uint8 G, Uint8 B, Uint8 A);
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
    explicit SDLException(const std::string& operation_desc);
    virtual const char* what() const throw();
};

class Renderer {
public:
    const Colors colors;
    Renderer(string WINDOW_TITLE, int WIDTH, int HEIGHT, bool FULL_SCREEN);
    void terminate();
    void clearScreen();
    void redraw();
    void drawLine(int X1, int Y1, int X2, int Y2, Color_RGBA COLOR);
    void drawLineHorizontal(int Y, int X1, int X2, Color_RGBA COLOR);
    void drawLineVertical(int X, int Y1, int Y2, Color_RGBA COLOR);
    void drawText(string TEXT, int TEXT_W, int TEXT_H, int TEXT_X, int TEXT_Y, Color_RGBA COLOR);
    void drawRect(SDL_Rect RECTANGLE_STRUCT, Color_RGBA COLOR);
    int windowWidth;
    int windowHeight;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
};

#endif //RAYMAGE_RENDERER_H
