#include <iostream>
#include "SDL.h"
#include "player.h"

//ToDo: Don't hardcode these
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
    SDL_Window* gWindow = nullptr; //Window to render to
    SDL_Surface* gScreenSurface = nullptr; //Surface contained by the window
    SDL_Renderer* gRenderer = nullptr; //The renderer
    bool game_loop = true;

    if (init(&gWindow, &gScreenSurface, &gRenderer) == 0){
        printf("Failed to initialize RayMage.\n");
    }
    else{
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);

        //Start handling the game loop
        SDL_Event e; //Event queue
        while (game_loop){

            while( SDL_PollEvent( &e ) != 0 ){ //Grab most recent event in queue; process it.
                if( e.type == SDL_QUIT ) {
                    game_loop = false;
                }
            }
        }
    }

    close(&gWindow, &gScreenSurface);
    return 0;
}