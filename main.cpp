/*
 * http://sdl.beuc.net/sdl.wiki/SDL_Rect
 *  "A SDL_Rect defines a rectangular area of pixels.
 *  It is used by SDL_BlitSurface to define blitting regions and by several other video functions.
 *
 *  http://sdl.beuc.net/sdl.wiki/SDL_UpdateRect
 *   "SDL_UpdateRect -- Makes sure the given area is updated on the given screen."
 *
 *  http://sdl.beuc.net/sdl.wiki/SDL_BlitSurface
 *   "This performs a fast blit from the source surface to the destination surface."
 *
 *  So using ray casting, use these methods to figure out where to draw rectangles, and blit them using blitsurface?
 *
 *  or it's SDL_RenderFillRect(),
 *  "fill a rectangle on the current rendering target with the drawing color."
 *  and "https://wiki.libsdl.org/SDL_SetRenderDrawColor"
 *  "set the color used for drawing operations (Rect, Line and Clear)."
 */


#include <iostream>
#include "SDL.h"
#include "test_map.h"
#include <string>
#include <math.h>
#include "cmath"

//ToDo: Don't hardcode these
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 460;

int init(SDL_Window** sdlWindow, SDL_Surface** sdlContainer, SDL_Renderer** sdlRenderer){
    //Set up SDL and create the window.
    int success = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else {
        *sdlWindow = SDL_CreateWindow("RayMage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (*sdlWindow == nullptr){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else {
            *sdlContainer = SDL_GetWindowSurface(*sdlWindow); //Grab the surface contained by the window
            *sdlRenderer = SDL_CreateRenderer(*sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(*sdlRenderer == nullptr) {
                SDL_DestroyWindow(*sdlWindow);
                printf("Couldn't create SDL renderer: %s", SDL_GetError());
                SDL_Quit();
                return 1;
            }
            success = 1;
        }
    }

    return success;
}

void close(SDL_Window** sdlWindow, SDL_Surface** sdlContainer){
    //Shut down SDL & destroy window

    SDL_FreeSurface(*sdlContainer);
    *sdlContainer = nullptr;

    SDL_DestroyWindow(*sdlWindow);
    *sdlWindow = nullptr;

    SDL_Quit();
}

int main() {
    bool game_loop = true;
    SDL_Window* gWindow = nullptr; //Window to render to
    SDL_Surface* gScreenSurface = nullptr; //Surface contained by the window
    SDL_Renderer* gRenderer = nullptr; //The renderer

    if (init(&gWindow, &gScreenSurface, &gRenderer) == 0){
        printf("Failed to initialize RayMage.\n");
    }
    else{
        //Set the renderer to initially be black, and then output its state.
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);

        int posX = 9, posY = 7;    // Initial Player position on the grid

        //Start handling the game loop
        SDL_Event e; //Event queue
        const Uint8 *keys = SDL_GetKeyboardState(NULL); //Is the key held down?
        while (game_loop){
            testMapGrid[posX][posY] = 5; // Set player location on grid to have value of 5


            //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
            //SDL_RenderDrawLine(gRenderer, x, drawStart, x, drawEnd);
            //SDL_RenderPresent(gRenderer);

            while( SDL_PollEvent( &e ) != 0 ){ //Grab most recent event in queue; process it.
                if( e.type == SDL_QUIT ) {
                    game_loop = false;
                }
                if (keys[SDL_SCANCODE_W]){
                    std::cout << "W is being pressed\n";
                }
                if (keys[SDL_SCANCODE_S]){
                    std::cout << "S is being pressed\n";
                }
                if (keys[SDL_SCANCODE_A]){
                    std::cout << "A is being pressed\n";
                }
                if (keys[SDL_SCANCODE_D]){
                    std::cout << "D is being pressed\n";
                }
            }
        }
    }

    close(&gWindow, &gScreenSurface);
    return 0;
}