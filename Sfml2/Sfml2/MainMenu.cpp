#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu() {
    if (!backgroundTexture.loadFromFile("MainMenu.png")) {
        std::cerr << "Failed to load main menu background\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!backgroundMusic.openFromFile("Assets/audio/mainmenu.wav")) {
        std::cerr << "Failed to load main menu music\n";
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50);
        backgroundMusic.play();
    }
}

void MainMenu::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle menu interactions here
}

void MainMenu::update() {
    // Update menu animations or logic
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
}
