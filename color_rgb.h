//
// Created by awilliams on 7/24/18.
//

#include <SDL_quit.h>

#ifndef RAYMAGE_COLOR_RGB_H
#define RAYMAGE_COLOR_RGB_H

#endif //RAYMAGE_COLOR_RGB_H

struct ColorRGB8bit;
//a color with 3 components: r, g and b
struct ColorRGB
{
    int r;
    int g;
    int b;

    ColorRGB(Uint8 r, Uint8 g, Uint8 b);
    ColorRGB(const ColorRGB8bit& color);
    ColorRGB();
};

ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2);
ColorRGB operator*(const ColorRGB& color, int a);
ColorRGB operator*(int a, const ColorRGB& color);
ColorRGB operator/(const ColorRGB& color, int a);
bool operator==(const ColorRGB& color, const ColorRGB& color2);
bool operator!=(const ColorRGB& color, const ColorRGB& color2);

static const ColorRGB RGB_Black    (  0,   0,   0);
static const ColorRGB RGB_Red      (255,   0,   0);
static const ColorRGB RGB_Green    (  0, 255,   0);
static const ColorRGB RGB_Blue     (  0,   0, 255);
static const ColorRGB RGB_Cyan     (  0, 255, 255);
static const ColorRGB RGB_Magenta  (255,   0, 255);
static const ColorRGB RGB_Yellow   (255, 255,   0);
static const ColorRGB RGB_White    (255, 255, 255);
static const ColorRGB RGB_Gray     (128, 128, 128);
static const ColorRGB RGB_Grey     (192, 192, 192);
static const ColorRGB RGB_Maroon   (128,   0,   0);
static const ColorRGB RGB_Darkgreen(  0, 128,   0);
static const ColorRGB RGB_Navy     (  0,   0, 128);
static const ColorRGB RGB_Teal     (  0, 128, 128);
static const ColorRGB RGB_Purple   (128,   0, 128);
static const ColorRGB RGB_Olive    (128, 128,   0);

//a color with 3 components: r, g and b
struct ColorRGB8bit
{
    Uint8 r;
    Uint8 g;
    Uint8 b;

    ColorRGB8bit(Uint8 r, Uint8 g, Uint8 b);
    ColorRGB8bit(const ColorRGB& color);
    ColorRGB8bit();
};

//a color with 3 components: h, s and l
struct ColorHSL
{
    int h;
    int s;
    int l;

    ColorHSL(Uint8 h, Uint8 s, Uint8 l);
    ColorHSL();
};

//a color with 3 components: h, s and v
struct ColorHSV
{
    int h;
    int s;
    int v;

    ColorHSV(Uint8 h, Uint8 s, Uint8 v);
    ColorHSV();
};
