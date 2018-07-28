//
// Created by awilliams on 7/27/18.
//

#include "keyscanner.h"


KeyScanner::KeyScanner() {
    this->e = {0};
    this->keys = nullptr;
}

void KeyScanner::scanKeys() {
    this->keys = SDL_GetKeyboardState(NULL);
}

bool KeyScanner::isKeyDown(SDL_Keycode key) {
    return (this->keys[SDL_GetScancodeFromKey(key)] != 0);
}

bool KeyScanner::isKeyDown(SDL_Scancode key) {
    return (this->keys[key] != 0);
}

bool KeyScanner::exitBtnPressed() {
    while (SDL_PollEvent(&this->e)) {
        if (this->e.type == SDL_QUIT) {
            return true;
        }
    }
}
