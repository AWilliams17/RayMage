//
// Created by awilliams on 7/28/18.
//

#include "player.h"

Player::Player(const double POS_X, const double POS_Y,
               const double DIR_X, const double DIR_Y,
               const double PLANE_X, const double PLANE_Y) {
    this->posX = POS_X, this->posY = POS_Y;
    this->dirX = DIR_X, this->dirY = DIR_Y;
    this->planeX = PLANE_X, this->planeY = PLANE_Y;
}
