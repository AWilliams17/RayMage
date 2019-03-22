//
// Created by awilliams on 8/1/18.
//

#include "raycaster.h"

Ray::Ray(const int SCREEN_WIDTH) {
    cameraX = 2 * SCREEN_WIDTH / double(SCREEN_WIDTH) - 1;
}

RayCaster::RayCaster(Renderer *RENDERER) {
    this->renderer = RENDERER;
}

void RayCaster::RenderWalls(Player *player, int map[24][24]) {
    Color_RGBA color(0, 0, 0, 0);
    for (int x = 0; x < this->renderer->windowWidth; x++) {
        Ray ray = Ray(this->renderer->windowWidth);

        // Calculate initial ray position and direction
        ray.cameraX = 2 * x / double(this->renderer->windowWidth) - 1; //x-coordinate in camera space
        ray.rayPosX = player->posX;
        ray.rayPosY = player->posY;
        ray.rayDirX = player->dirX + player->planeX * ray.cameraX;
        ray.rayDirY = player->dirY + player->planeY * ray.cameraX;

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

        // Perform DDA (https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
        while (!ray.wallHit) {
            // Jump to the next square in the grid, or in x or y-direction.
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
            int tileIndex = map[ray.mapX][ray.mapY];
            if (tileIndex > 0 && tileIndex != 5) {
                ray.wallHit = 1;
            }
        }

        // Calculate the projected camera distance. Oblique distance results in the fish eye effect
        // (https://gamedev.stackexchange.com/questions/45295/raycasting-fisheye-effect-question?rq=1)
        if (ray.side == 0) {
            ray.perpWallDist = fabs((ray.mapX - ray.rayPosX + (1.0 - ray.stepX) / 2) / ray.rayDirX);
        } else {
            ray.perpWallDist = fabs((ray.mapY - ray.rayPosY + (1.0 - ray.stepY) / 2) / ray.rayDirY);
        }

        // Calculate the height of the line to draw on the screen
        int lineHeight = abs(int(this->renderer->windowHeight / ray.perpWallDist));

        // Calculate the lowest and the highest pixel to fill in the current stripe
        int drawStart = -lineHeight / 2 + this->renderer->windowHeight / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }
        int drawEnd = lineHeight / 2 + this->renderer->windowHeight / 2;
        if (drawEnd >= this->renderer->windowHeight) {
            drawEnd = this->renderer->windowHeight - 1;
        }

        // Choose the wall color
        switch (map[ray.mapX][ray.mapY]) {
            case 1:
                color = this->renderer->colors.RED;
                break; //red
            case 2:
                color = this->renderer->colors.GREEN;
                break; //green
            case 3:
                color = this->renderer->colors.BLUE;
                break; //blueY
            case 4:
                color = this->renderer->colors.WHITE;
                break; //white
            default:
                color = this->renderer->colors.YELLOW;
                break; //yellow
        }

        // Give X and Y sides different brightnesses
        if (ray.side == 1) {
            color.R /= 2;
            color.G /= 2;
            color.B /= 2;
        }

        // Draw the resulting line
        this->renderer->drawLineVertical(x, drawStart, drawEnd, color);
    }
}
