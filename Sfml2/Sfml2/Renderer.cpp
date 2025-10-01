#include "Renderer.h"
#include <iostream>

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode(width, height), title), shape(100.f)
{
    // Load title background
    if (!backgroundTexture.loadFromFile("Titlescreen.png")) {
        std::cerr << "Failed to load title background\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Load font and set up title text
    if (!font.loadFromFile("Assets/fonts/ReggaeOne.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    titleText.setFont(font);
    titleText.setString("Click to Start");
    titleText.setCharacterSize(51);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(450, 890);

    
    // Load and play title music
    if (!backgroundMusic.openFromFile("Assets/audio/titleview.wav")) {
        std::cerr << "Failed to load title music\n";
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50);
        backgroundMusic.play();
    }
}

void Renderer::run() {
    bool showTitle = true;
    bool startGame = false;
    bool openCodes = false;
    bool quitGame = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                showTitle = false;

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!isMainMenu) {
                    isMainMenu = true;
                    backgroundMusic.stop();
                    mainMenu = std::make_unique<MainMenu>(window.getSize());
                }
            }
        }
            if (isMainMenu && mainMenu) {
                mainMenu->handleEvent(event, window, startGame, openCodes, quitGame);
        }

        window.clear();

        if (isMainMenu && mainMenu) {
            mainMenu->draw(window);
        }
        else {
            window.draw(backgroundSprite);

            if (showTitle) {
                window.draw(titleText);
            }
            else {
                window.draw(shape);
            }

            
        }

        window.display();
        // ? NOW check quitGame after drawing
        if (quitGame) {
            std::cout << "Quit button clicked\n";
            window.close();
        }
    }
}
