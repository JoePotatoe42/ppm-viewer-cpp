#ifndef READ_FILE_h
#define READ_FILE_h

#include <fstream>
#include <vector>
#include "PPMImage.h"

inline void skipComments(std::ifstream& file)
{
    while (file >> std::ws && file.peek() == '#') {
        std::string line;
        std::getline(file, line);
    }
}

inline PPMImage readHeader(std::ifstream& file)
{
    PPMImage image_header;

    skipComments(file);
    file >> image_header.format;
    
    skipComments(file);
    file >> image_header.width;

    skipComments(file);
    file >> image_header.height;

    skipComments(file);
    file >> image_header.max_color;

    return image_header;
}

inline RGB readP3Pixel(std::ifstream& file, int max_color)
{
    RGB color;
    file >> color.r;
    file >> color.g;
    file >> color.b;

    if (max_color != 255) {
        color.r = (color.r * 255) / max_color;
        color.g = (color.g * 255) / max_color;
        color.b = (color.b * 255) / max_color;
    }

    return color;
}

inline RGB readP6Pixel(std::ifstream& file, int max_color)
{
    // In P6 data is stored as bytes
    // I want to interpret it as numbers (0-255)
        unsigned char rgb[3];
        auto buffer = reinterpret_cast<char*>(rgb);
        file.read(buffer, 3);
        RGB color(rgb[0], rgb[1], rgb[2]);

        if (max_color != 255) {
        color.r = (color.r * 255) / max_color;
        color.g = (color.g * 255) / max_color;
        color.b = (color.b * 255) / max_color;
    }

    return color;
}

inline std::vector<RGB> readAllPixels(std::ifstream& file, const PPMImage& image)
{

    int size = image.height * image.width;
    std::vector<RGB> buffer(size);

    if (image.format == "P6")
    {
        // consumes the single whitespace before the raster
        file >> std::ws; 

        for (int i = 0; i < size; i++)
        {
            buffer[i] = readP6Pixel(file,image.max_color);
        }
    }
    else
    {
        for(int i = 0; i < size; i++)
         {
            buffer[i]= readP3Pixel(file, image.max_color);
         }
    }
    
    return buffer;
}
#endif