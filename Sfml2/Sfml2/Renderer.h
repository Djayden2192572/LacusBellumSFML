#pragma once
#include <SFML/Graphics.hpp>

class Renderer {
public:
    Renderer(unsigned int width, unsigned int height, const std::string& title);
    void run();

private:
    sf::RenderWindow window;
    sf::CircleShape shape;
    sf::Font font;
    sf::Text titleText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

};