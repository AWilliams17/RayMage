//
// Created by awilliams on 7/24/18.
//

#include "color_rgb.h"
namespace color_RGB{
    ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    ColorRGB::ColorRGB(const ColorRGB8bit& color)
    {
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
    }
    ColorRGB::ColorRGB()
    {
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }
    ColorRGB8bit::ColorRGB8bit(Uint8 r, Uint8 g, Uint8 b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    ColorRGB8bit::ColorRGB8bit(const ColorRGB& color)
    {
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
    }
    ColorRGB8bit::ColorRGB8bit()
    {
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }

//Add two colors
    ColorRGB operator+(const ColorRGB& color, const ColorRGB& color2)
    {
        ColorRGB c;
        c.r = color.r + color2.r;
        c.g = color.g + color2.g;
        c.b = color.b + color2.b;
        return c;
    }

//Subtract two colors
    ColorRGB operator-(const ColorRGB& color, const ColorRGB& color2)
    {
        ColorRGB c;
        c.r = color.r - color2.r;
        c.g = color.g - color2.g;
        c.b = color.b - color2.b;
        return c;
    }

//Multiplies a color with an integer
    ColorRGB operator*(const ColorRGB& color, int a)
    {
        ColorRGB c;
        c.r = color.r * a;
        c.g = color.g * a;
        c.b = color.b * a;
        return c;
    }

//Multiplies a color with an integer
    ColorRGB operator*(int a, const ColorRGB& color)
    {
        ColorRGB c;
        c.r = color.r * a;
        c.g = color.g * a;
        c.b = color.b * a;
        return c;
    }

//Divides a color through an integer
    ColorRGB operator/(const ColorRGB& color, int a)
    {
        if(a == 0) return color;
        ColorRGB c;
        c.r = color.r / a;
        c.g = color.g / a;
        c.b = color.b / a;
        return c;
    }

//Are both colors equal?
    bool operator==(const ColorRGB& color, const ColorRGB& color2)
    {
        return(color.r == color2.r && color.g == color2.g && color.b == color2.b);
    }

//Are both colors not equal?
    bool operator!=(const ColorRGB& color, const ColorRGB& color2)
    {
        return(!(color.r == color2.r && color.g == color2.g && color.b == color2.b));
    }

    ColorHSL::ColorHSL(Uint8 h, Uint8 s, Uint8 l)
    {
        this->h = h;
        this->s = s;
        this->l = l;
    }
    ColorHSL::ColorHSL()
    {
        this->h = 0;
        this->s = 0;
        this->l = 0;
    }
    ColorHSV::ColorHSV(Uint8 h, Uint8 s, Uint8 v)
    {
        this->h = h;
        this->s = s;
        this->v = v;
    }
    ColorHSV::ColorHSV()
    {
        this->h = 0;
        this->s = 0;
        this->v = 0;
    }
}