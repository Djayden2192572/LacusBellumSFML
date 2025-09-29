#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>   //  sf::Music
#include <string>

class Renderer {
public:
    Renderer(unsigned int width, unsigned int height, const std::string& title);
    void run();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::CircleShape shape;
    sf::Text titleText;

    sf::Music backgroundMusic;  //  Persistent 
};
