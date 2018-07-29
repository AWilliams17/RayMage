#include "player.h"
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

    Renderer renderer("RayMage", SCREEN_WIDTH, SCREEN_HEIGHT, false);
    renderer.clearScreen();

    Player player = Player(22, 12, -1, 0, 0, 0.66);
    Color_RGBA color(0, 0, 0, 0);

    while (game_loop) { // pretty much all from https://lodev.org/cgtutor/raycasting.html#Untextured_Raycaster_
        testMapGrid[int(player.posX)][int(player.posY)] = 5;
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            Ray ray = Ray(SCREEN_WIDTH);

            // Calculate initial ray position and direction
            ray.cameraX = 2 * x / double(SCREEN_WIDTH) - 1; //x-coordinate in camera space
            ray.rayPosX = player.posX;
            ray.rayPosY = player.posY;
            ray.rayDirX = player.dirX + player.planeX * ray.cameraX;
            ray.rayDirY = player.dirY + player.planeY * ray.cameraX;

            // Record what box of the grid the ray is in
            ray.mapX = int(ray.rayPosX);
            ray.mapY = int(ray.rayPosY);

            // Record the length of the ray from the current position to the next x/y side
            ray.sideDistX, ray.sideDistY;

            // Record the length of the ray from one x/y-side to the next x/y-side
            ray.deltaDistX = sqrt(1 + (ray.rayDirY * ray.rayDirY) / (ray.rayDirX * ray.rayDirX));
            ray.deltaDistY = sqrt(1 + (ray.rayDirX * ray.rayDirX) / (ray.rayDirY * ray.rayDirY));
            ray.perpWallDist;


            // Calculate the stepX and initial sideDistX
            ray.stepX = 1;
            ray.sideDistX = (ray.mapX + 1.0 - ray.rayPosX) * ray.deltaDistX;
            if (ray.rayDirX < 0) {
                ray.stepX = -1;
                ray.sideDistX = (ray.rayPosX - ray.mapX) * ray.deltaDistX;
            }

            // Calculate the stepY and initial sideDistY
            ray.stepY = 1;
            ray.sideDistY = (ray.mapY + 1.0 - ray.rayPosY) * ray.deltaDistY;
            if (ray.rayDirY < 0) {
                ray.stepY = -1;
                ray.sideDistY = (ray.rayPosY - ray.mapY) * ray.deltaDistY;
            }

            //perform DDA (https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
            while (!ray.wallHit) {
                // Jump to the next square in the grid, or in x or y-direction
                if (ray.sideDistX < ray.sideDistY) {
                    ray.sideDistX += ray.deltaDistX;
                    ray.mapX += ray.stepX;
                    ray.side = 0;
                } else {
                    ray.sideDistY += ray.deltaDistY;
                    ray.mapY += ray.stepY;
                    ray.side = 1;
                }
                // Check if the ray has hit a wall. If it has, end the loop.
                int tileIndex = testMapGrid[ray.mapX][ray.mapY];
                if (tileIndex > 0 && tileIndex != 5) {
                    ray.wallHit = 1;
                }
            }

            // Calculate the projected camera distance. Oblique distance results in the fish eye effect
            // (https://gamedev.stackexchange.com/questions/45295/raycasting-fisheye-effect-question?rq=1)
            if (ray.side == 0) {
                ray.perpWallDist = fabs((ray.mapX - ray.rayPosX + (1 - ray.stepX) / 2) / ray.rayDirX);
            } else {
                ray.perpWallDist = fabs((ray.mapY - ray.rayPosY + (1 - ray.stepY) / 2) / ray.rayDirY);
            }

            // Calculate the height of the line to draw on the screen
            int lineHeight = abs(int(SCREEN_HEIGHT / ray.perpWallDist));

            // Calculate the lowest and the highest pixel to fill in the current stripe
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0) {
                drawStart = 0;
            }
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT) {
                drawEnd = SCREEN_HEIGHT - 1;
            }

            // Choose the wall color
            switch (testMapGrid[ray.mapX][ray.mapY]) {
                case 1:
                    color = renderer.colors.RED;
                    break; //red
                case 2:
                    color = renderer.colors.GREEN;
                    break; //green
                case 3:
                    color = renderer.colors.BLUE;
                    break; //blueY
                case 4:
                    color = renderer.colors.WHITE;
                    break; //white
                default:
                    color = renderer.colors.YELLOW;
                    break; //yellow
            }

            // Give X and Y sides different brightnesses
            if (ray.side == 1) {
                color.R /= 2;
                color.G /= 2;
                color.B /= 2;
            }

            // Draw the resulting line
            renderer.drawLineVertical(x, drawStart, drawEnd, color);
        }

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

        oldTime = currTime;
        currTime = SDL_GetTicks();

        double frameTime = (currTime - oldTime) / 1000.0;
        int FPS = (int) (1.0 / frameTime);

        renderer.drawText("FPS:", 0, 0, SCREEN_WIDTH - 67, 0, renderer.colors.BLUE);
        renderer.drawText(std::to_string(FPS), 0, 0, SCREEN_WIDTH - 24, 0, renderer.colors.YELLOW);
        renderer.redraw();
        renderer.clearScreen();

        // Movement speed is constant
        double movementSpeed = frameTime * 5.0;
        double rotationSpeed = frameTime * 3.0;

        if (keyScanner.exitBtnPressed()) {
            game_loop = false;
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
