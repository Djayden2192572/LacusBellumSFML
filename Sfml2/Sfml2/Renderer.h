#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "MainMenu.h"

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
    sf::Font font;
    sf::Music backgroundMusic;

    std::unique_ptr<MainMenu> mainMenu;
    bool isMainMenu = false;
};
