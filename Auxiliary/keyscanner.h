//
// Created by awilliams on 7/27/18.
//

#ifndef RAYMAGE_KEYS_H
#define RAYMAGE_KEYS_H

#include "SDL.h"

class KeyScanner {
public:
    KeyScanner();
    bool isKeyDown(SDL_Keycode key);
    bool isKeyDown(SDL_Scancode key);
    bool exitBtnPressed();
private:
    SDL_Event e;
    const Uint8 *keys;
};

#endif //RAYMAGE_KEYS_H
