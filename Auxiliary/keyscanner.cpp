//
// Created by awilliams on 7/27/18.
//

#include "keyscanner.h"


KeyScanner::KeyScanner() {
    this->e = {0};
    this->keys = SDL_GetKeyboardState(NULL);
}

// https://wiki.libsdl.org/CategoryKeyboard
bool KeyScanner::isKeyDown(SDL_Keycode key) { // Key code == Maps to layout of keyboard; correlates with scan code.
    return (this->keys[SDL_GetScancodeFromKey(key)] != 0);
}

bool KeyScanner::isKeyDown(SDL_Scancode key) { // Scan code == Physical location of key on keyboard.
    return (this->keys[key]);
}

bool KeyScanner::exitBtnPressed() {
    while (SDL_PollEvent(&this->e)) {
        if (this->e.type == SDL_QUIT) {
            return true;
        }
    }
}
