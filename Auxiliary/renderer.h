//
// Created by awilliams on 7/27/18.
//

#ifndef RAYMAGE_RENDERER_H
#define RAYMAGE_RENDERER_H

#include "SDL.h"
#include "string"

typedef std::string string;

class SDLException : public std::exception {
    string m_msg;
public:
    SDLException(const std::string& operation_desc);
    virtual const char* what() const throw();
};

class Renderer {
public:
    Renderer(const string WINDOW_TITLE, const int WIDTH, const int HEIGHT, const bool FULL_SCREEN);
    int terminate();
    int clearScreen();
    int redraw();
    int drawLine(int x1, int y1, int x2, int y2);
    int drawLineHorizontal(int y, int x1, int x2);
    int drawLineVertical(int x, int y1, int y2);
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif //RAYMAGE_RENDERER_H
