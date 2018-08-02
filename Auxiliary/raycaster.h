//
// Created by awilliams on 8/1/18.
//

#ifndef RAYMAGE_RAYCASTER_H
#define RAYMAGE_RAYCASTER_H

#include <SDL_system.h>
#include "SDL.h"
#include "renderer.h"
#include "../player.h"

typedef struct Ray {
    Ray(const int SCREEN_WIDTH);
    double cameraX;
    double rayDirX, rayDirY;
    double sideDistX, sideDistY;
    double deltaDistX, deltaDistY;
    double perpWallDist;
    double rayPosX, rayPosY;
    int mapX, mapY;
    int stepX, stepY;
    bool wallHit = false;
    bool side = 0;
};


class RayCaster {
public:
    RayCaster(Renderer *RENDERER);
    void RenderWalls(Player *player, int map[24][24]);
private:
    Renderer *renderer = nullptr;
};

#endif //RAYMAGE_RAYCASTER_H
