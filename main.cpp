#include "Auxiliary/renderer.h"
#include "Auxiliary/keyscanner.h"
#include "test_map.h"

int main() {
    bool game_loop = true;
    KeyScanner keyScanner;

    Renderer renderer("RayMage", 640, 480, false);
    renderer.clearScreen();

    while (game_loop) {
        keyScanner.scanKeys();

        if (keyScanner.exitBtnPressed()){
            game_loop = false;
        }
    }

    return 0;
}
