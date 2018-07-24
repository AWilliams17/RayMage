//
// Created by awilliams on 7/24/18.
//

#ifndef RAYMAGE_PLAYER_H
#define RAYMAGE_PLAYER_H

struct line_result;

class player{
public:
    player(const int START_X, const int START_Y, const int FOV, const int SCREEN_HEIGHT);
    line_result doRayCast();
private:
    double posX, posY; //Position vectors - where the player is on the map
    double dirX = -1, dirY = 0; //Direction vectors - what direction the player is facing.
    double planeX = 0, planeY; //Plane vectors - the camera plane of the player, perpendicular to direction
    int screenHeight;
    inline void calcStepAndSideDist(const double RAY_DIR_X, const double RAY_DIR_Y, const double DELTA_X, const double DELTA_Y,
                                    int *stepX, int *stepY, double *sideDistX, double *sideDistY);
};

#endif //RAYMAGE_PLAYER_H

