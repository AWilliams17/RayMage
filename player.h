//
// Created by awilliams on 7/28/18.
//

#ifndef RAYMAGE_PLAYER_H
#define RAYMAGE_PLAYER_H

typedef struct Player {
    Player(double POS_X, double POS_Y, double DIR_X,
           double DIR_Y, double PLANE_X, double PLANE_Y);
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
};


#endif //RAYMAGE_PLAYER_H
