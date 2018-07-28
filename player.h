//
// Created by awilliams on 7/28/18.
//

#ifndef RAYMAGE_PLAYER_H
#define RAYMAGE_PLAYER_H


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

typedef struct Player {
    Player(const double POS_X, const double POS_Y, const double DIR_X,
           const double DIR_Y, const double PLANE_X, const double PLANE_Y);
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
};


#endif //RAYMAGE_PLAYER_H
