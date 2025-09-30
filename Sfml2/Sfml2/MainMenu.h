#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MainMenu {
public:
    MainMenu();
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music backgroundMusic;
};
