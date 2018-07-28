#include "Auxiliary/renderer.h"
#include "Auxiliary/keyscanner.h"
#include "test_map.h"

int main() {
    bool game_loop = true;

    Renderer renderer("RayMage", 640, 480, false);
    renderer.clearScreen();
    renderer.drawLineVertical(55, 100, 200, renderer.colors.RED);
    renderer.redraw();

    KeyScanner keyScanner;

    while (game_loop) {
        keyScanner.scanKeys();

        if (keyScanner.exitBtnPressed()){
            printf("Test");
            game_loop = false;
        }
        if (keyScanner.isKeyDown(SDLK_w)) {
            printf("Test");
            game_loop = false;
        }
    }
    return 0;
}
