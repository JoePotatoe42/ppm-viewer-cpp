#ifndef PPMImage_H
#define PPMImage_H

#include <iostream>

struct RGB{
        int r;
        int g;
        int b;
    RGB() : r(0), g(0), b(0) {}
    RGB(int r, int g, int b) : r(r), g(g), b(b) {}
};

struct PPMImage
{
        std::string format;
        int width;
        int height;
        int max_color;
    PPMImage() : format(""), width(0), height(0), max_color(0) {}
    PPMImage(std::string format, int width, int height, int max_color) : format(format),
    width(width), height(height), max_color(max_color) {}    
    bool isWrongFormat(){
        if (this->format == "P3" || this->format == "P6") return false;
        return true;
    }

};

inline std::ostream& operator<<(std::ostream& out, const PPMImage& image)
{
    return out << image.format << ' ' << image.width << ' '
               << image.height << ' ' << image.max_color;
}

inline std::ostream& operator<<(std::ostream& out, const RGB& color)
{
    return out << color.r << ' ' << color.g << ' ' << color.b;
}


#endif