// ToDo: Make it use textures.
// ToDo: Make this more OOP. Clean the game_loop up, it's a mess.
// ToDo: Proper SDL Error Handling.
// ToDo: Better map format.
// ToDo: ...Map editor? :D
// ToDo: Strafing + Turning while moving.
#include "player.h"
#include "Auxiliary/raycaster.h"
#include "Auxiliary/renderer.h"
#include "Auxiliary/keyscanner.h"
#include "test_map.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main() {
    bool game_loop = true;
    double currTime = 0;
    double oldTime = 0;

    KeyScanner keyScanner;

    Renderer renderer = Renderer("RayMage", SCREEN_WIDTH, SCREEN_HEIGHT, false);
    Player player = Player(22, 12, -1, 0, 0, 0.66);
    RayCaster rayCaster = RayCaster(&renderer);
    Color_RGBA color(0, 0, 0, 0);
    renderer.clearScreen();

    while (game_loop) { // pretty much all from https://lodev.org/cgtutor/raycasting.html#Untextured_Raycaster_
        testMapGrid[int(player.posX)][int(player.posY)] = 5;

        rayCaster.RenderWalls(&player, testMapGrid);

        for (int i = 0; i < MAPX; i++) {
            for (int j = 0; j < MAPY; j++) {
                SDL_Rect rect = SDL_Rect{i * 4, j * 4, 3, 3};

                int mapTile = testMapGrid[j][i];

                if (mapTile == 0) {
                    color = renderer.colors.BLACK;
                } else if (mapTile == 1) {
                    color = renderer.colors.RED;
                } else if (mapTile == 2) {
                    color = renderer.colors.GREEN;
                } else if (mapTile == 3) {
                    color = renderer.colors.BLUE;
                } else if (mapTile == 5) {
                    color = renderer.colors.YELLOW;
                }
                renderer.drawRect(rect, color);
            }
        }

        // FPS counter + crosshair
        oldTime = currTime;
        currTime = SDL_GetTicks();

        double frameTime = (currTime - oldTime) / 1000.0;
        int FPS = (int) (1.0 / frameTime);

        renderer.drawText("FPS:", 0, 0, renderer.windowWidth - 67, 0, renderer.colors.BLUE);
        renderer.drawText(std::to_string(FPS), 0, 0, renderer.windowWidth - 24, 0, renderer.colors.YELLOW);
        renderer.drawText("+", 0, 0, (renderer.windowWidth / 2), (renderer.windowHeight / 2), renderer.colors.TEAL);
        renderer.redraw();
        renderer.clearScreen();

        // Movement speed is constant
        double movementSpeed = frameTime * 5.0;
        double rotationSpeed = frameTime * 3.0;

        if (keyScanner.exitBtnPressed()) {
            game_loop = false;
            renderer.terminate();
        } else {
            if (keyScanner.isKeyDown(SDL_SCANCODE_W)) {
                // Add player's DirX to PosX,
                // Add player's DirY to PosY
                // (assume DirX and DirY are normalized vectors - length is 1)
                // If new position is inside wall, don't move.
                testMapGrid[int(player.posX)][int(player.posY)] = 0;
                if (testMapGrid[int(player.posX + player.dirX * movementSpeed)][int(player.posY)] == 0) {
                    player.posX += player.dirX * movementSpeed;
                }
                if (testMapGrid[int(player.posX)][int(player.posY + player.dirY * movementSpeed)] == 0) {
                    player.posY += player.dirY * movementSpeed;
                }
            } else if (keyScanner.isKeyDown(SDLK_s)) { // Same as above, only subtraction.
                testMapGrid[int(player.posX)][int(player.posY)] = 0;
                if (testMapGrid[int(player.posX - player.dirX * movementSpeed)][int(player.posY)] == 0) {
                    player.posX -= player.dirX * movementSpeed;
                }
                if (testMapGrid[int(player.posX)][int(player.posY + player.dirY * movementSpeed)] == 0) {
                    player.posY -= player.dirY * movementSpeed;
                }
            } else if (keyScanner.isKeyDown(SDLK_d)) {
                //Rotate the direction AND plane vector
                double oldDirX = player.dirX;
                player.dirX = player.dirX * cos(-rotationSpeed) - player.dirY * sin(-rotationSpeed);
                player.dirY = oldDirX * sin(-rotationSpeed) + player.dirY * cos(-rotationSpeed);
                double oldPlaneX = player.planeX;
                player.planeX = player.planeX * cos(-rotationSpeed) - player.planeY * sin(-rotationSpeed);
                player.planeY = oldPlaneX * sin(-rotationSpeed) + player.planeY * cos(-rotationSpeed);
            } else if (keyScanner.isKeyDown(SDLK_a)) {
                double oldDirX = player.dirX;
                player.dirX = player.dirX * cos(rotationSpeed) - player.dirY * sin(rotationSpeed);
                player.dirY = oldDirX * sin(rotationSpeed) + player.dirY * cos(rotationSpeed);
                double oldPlaneX = player.planeX;
                player.planeX = player.planeX * cos(rotationSpeed) - player.planeY * sin(rotationSpeed);
                player.planeY = oldPlaneX * sin(rotationSpeed) + player.planeY * cos(rotationSpeed);
            }
        }
    }
    return 0;
}
