//
// Created by awilliams on 7/24/18.
//

#include <cmath>
#include <iostream>
#include "player.h"
#include "test_map.h"
#include "color_rgb.h"

class player {
public:
    struct line_result {
        int x, drawStart, drawEnd;
        ColorRGB color;
    };

    player(const int START_X, const int START_Y, const int FOV, const int SCREEN_HEIGHT){
        posX = START_X, posY = START_Y;
        planeY = 2 * atan((FOV * 0.01) / 1.0); // Ratio between length of direction and camera plane determines FOV.
        screenHeight = SCREEN_HEIGHT;
    }
    line_result doRayCast(){
        for (int x = 0; x < MAPX; x++){
            double cameraX = 2 * x / double(MAPY) - 1;
            double rayDirX = dirX + planeY * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            //These are the current square the projected ray is in.
            auto mapX = int(posX), mapY = int(posY);

            //How far from the next x or y side we are
            double sideDistX, sideDistY;

            //Length of ray from one x/y side to another x/y side.
            double deltaDistX = std::abs(1 / rayDirX), deltaDistY = std::abs(1 / rayDirY);
            double perpWallDist;

            //What direction to step in the x or y direction (+1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //Detect if a wall was hit.
            int side; //NS or EW wall hit detection.

            /*
             * stepX, stepY, sideDistX, sideDistY have to be calculated before proceeding.
             * if the ray direction has a negative x or y, then set them according to -1 or +1.
             * if the ray direction has a 0, it won't matter since it won't get used.
             *
             * if the ray direction has a negative x, then sideDistX is just the distance from the ray starting
             * position to the first side on the left. If it's a positive x, then it's the first side on the right.
             * if the ray direction has a negative y, it's the same logic, only with the first side ABOVE or BELOW
             * the position.
             */
            calcStepAndSideDist(rayDirX, rayDirY, deltaDistX, deltaDistY, &stepX, &stepY, &sideDistX, &sideDistY);

            //Perform DD
            while (hit == 0){
                if (sideDistX < sideDistY){
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else{
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                //Check if ray has hit wall.
                if (testMapGrid[mapX][mapY] > 0) hit = 1;
            }

            //Calculate distance projected on camera direction
            if (side == 0){
                perpWallDist = fabs((mapX - posX + (1 - stepX) / 2) / rayDirX);
            }
            else{
                perpWallDist = fabs((mapY - posY + (1 - stepY) / 2) / rayDirY);
            }

            //Calculate height of line to draw on screen
            int lineHeight = abs(int(screenHeight / perpWallDist));

            //Calculate the lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + screenHeight / 2;
            if (drawStart < 0){
                drawStart = 0;
            }
            int drawEnd = lineHeight / 2 + screenHeight / 2;
            if (drawEnd >= screenHeight){
                drawEnd = screenHeight - 1;
            }

            //Choose the wall color
            ColorRGB color;
            switch(testMapGrid[mapX][mapY])
            {
                case 1:  color = RGB_Red;  break; //red
                case 2:  color = RGB_Green;  break; //green
                case 3:  color = RGB_Blue;   break; //blue
                case 4:  color = RGB_White;  break; //white
                default: color = RGB_Yellow; break; //yellow
            }

            //give x and y sides different brightness
            if (side == 1) {color = color / 2;}

            //return pixels of stripe as vertical line to be drawn in the main loop
            return {x, drawStart, drawEnd, color};
        }
    }

private:
    double posX, posY; //Position vectors - where the player is on the map
    double dirX = -1, dirY = 0; //Direction vectors - what direction the player is facing.
    double planeX = 0, planeY; //Plane vectors - the camera plane of the player, perpendicular to direction
    int screenHeight;
    inline void calcStepAndSideDist(const double RAY_DIR_X, const double RAY_DIR_Y, const double DELTA_X, const double DELTA_Y,
                           int *stepX, int *stepY, double *sideDistX, double *sideDistY){
        if (RAY_DIR_X < 0){
            *stepX = 1;
            *sideDistX = (posX - MAPX) * DELTA_X;
        }
        else{
            *stepX = -1;
            *sideDistX = (MAPX + 1.0 - posX) * DELTA_X;
        }
        if (RAY_DIR_Y < 0){
            *stepY = -1;
            *sideDistY = (posY - MAPY) * DELTA_Y;
        }
        else{
            *stepY = 1;
            *sideDistY = (MAPY - 1.0 - posY) * DELTA_Y;
        }
    }
};