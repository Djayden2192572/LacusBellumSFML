#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

class MainMenu {
public:
    MainMenu(sf::Vector2u windowSize);
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window,
        bool& startGame, bool& openCodes, bool& quitGame);

private:
    sf::Font font;
    sf::Text startButton;
    sf::Text codeButton;
    sf::Text quitButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music backgroundMusic;
    

};
