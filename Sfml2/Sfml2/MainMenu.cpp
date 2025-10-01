#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::Vector2u windowSize) {
    if (!font.loadFromFile("Assets/fonts/ReggaeOne.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    
    if (!backgroundMusic.openFromFile("Assets/audio/mainmenu.wav")) {
        std::cerr << "Failed to load main menu music\n";
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50);
        backgroundMusic.play();
    }
    if (!backgroundTexture.loadFromFile("MainMenu.png")) {
        std::cerr << "Failed to load main menu background\n";
    }


    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
        static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
        

    );


    float centerX = windowSize.x / 2.f;

    startButton.setFont(font);
    startButton.setString("Start Game");
    startButton.setCharacterSize(51);
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(centerX - 600, 600);

    codeButton.setFont(font);
    codeButton.setString("Codes");
    codeButton.setCharacterSize(51);
    codeButton.setFillColor(sf::Color::White);
    codeButton.setPosition(centerX -  600, 690);

    quitButton.setFont(font);
    quitButton.setString("Quit");
    quitButton.setCharacterSize(51);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition(centerX - 600, 780);
}


void MainMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(startButton);
    window.draw(codeButton);
    window.draw(quitButton);
}


void MainMenu::handleEvent(const sf::Event& event, sf::RenderWindow& window,
    bool& startGame, bool& openCodes, bool& quitGame) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (startButton.getGlobalBounds().contains(mousePos)) {
            startGame = true;
        }
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (quitButton.getGlobalBounds().contains(mousePos)) {
                quitGame = true;
            }
        }

        else if (codeButton.getGlobalBounds().contains(mousePos)) {
            openCodes = true;
        }
        else if (quitButton.getGlobalBounds().contains(mousePos)) {
            quitGame = true;
        }
    }
}
