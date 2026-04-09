#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "PPMImage.h"
#include <vector>
#include <optional>


inline sf::Texture generateTexture(const unsigned int width, const unsigned int height, const std::vector<RGB>& data)
{
    sf::Texture texture(sf::Vector2u(width, height));
    std::vector<uint8_t> pixels(width * height * 4);

    for (std::size_t i = 0; i < data.size(); i++)
    {
        pixels[i*4+0] = data[i].r;
        pixels[i*4+1] = data[i].g;
        pixels[i*4+2] = data[i].b;
        pixels[i*4+3] = 255;
    }

    texture.update(pixels.data());
    
    return texture;
}

inline std::string generateWindowName(const std::string& file_address)
{
    std::filesystem::path p(file_address);
    return p.stem().string();
}


// create the window
inline void createWindow(const unsigned int width, const unsigned int height, const std::string& name, const std::vector<RGB>& data)
{
    sf::RenderWindow window(sf::VideoMode({width,height}), generateWindowName(name));
    sf::Texture texture = generateTexture(width,height,data);
    sf::Sprite sprite(texture);
    
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
         if (event->is<sf::Event::Closed>())
         window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(sprite);

        // end the current frame
        window.display();
    }
}

#endif