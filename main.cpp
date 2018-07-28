#include "Auxiliary/renderer.h"
#include "test_map.h"

int main() {
    bool game_loop = true;

    Renderer renderer("RayMage", 640, 480, false);
    renderer.clearScreen();
    renderer.drawLineVertical(55, 100, 200);
    renderer.redraw();

    while (game_loop) {

    }
    return 0;
}
