#include "Renderer.h"
#include <iostream>
#include "Player.h"
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
    bool inGame = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!inGame) {
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
            if (isMainMenu && mainMenu && !inGame) {
                mainMenu->handleEvent(event, window, startGame, openCodes, quitGame);
            }
        }

        // Transition to game when startGame is true
        if (startGame && !inGame) {
            inGame = true;
            mainMenu.reset(); // Hide main menu
        }

        window.clear();

        if (inGame) {
            // --- GAME SCREEN START ---
            window.clear(sf::Color(50, 50, 150)); // Game background

            window.draw(player); // <-- Add this line to draw your player sprite

            // You can draw other game objects here later
            // --- GAME SCREEN END ---
        }
        else if (isMainMenu && mainMenu) {
            mainMenu->draw(window);
        }
        else {
            window.draw(backgroundSprite);
            if (showTitle) {
                window.draw(titleText);
            } else {
                window.draw(shape);
            }
        }

        window.display();

        if (quitGame) {
            std::cout << "Quit button clicked\n";
            window.close();
        }
    }
}
