#include "Playscreen.h"
#include <iostream>


PlayScreen::PlayScreen(sf::Vector2u windowSize, int stageNumber) : stage(stageNumber) {
    std::string bgPath = "Assets/images/stage" + std::to_string(stage) + "GameBG.png";
    std::string musicPath = "Assets/audio/stage" + std::to_string(stage) + "_theme.wav";
    // Example wall layout
    walls.emplace_back(sf::Vector2f(100, 1000), sf::Vector2f(1700, 40)); // Horizontal
    walls.emplace_back(sf::Vector2f(100, 99), sf::Vector2f(1700, 40)); // Horizontal
    walls.emplace_back(sf::Vector2f(100, 30), sf::Vector2f(40, 1000)); // Vertical
    walls.emplace_back(sf::Vector2f(1750, 30), sf::Vector2f(40, 1000)); // Vertical

    if (!backgroundTexture.loadFromFile(bgPath)) {
        std::cerr << "Failed to load background for stage " << stage << "\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
        static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
    );

    if (!stageMusic.openFromFile(musicPath)) {
        std::cerr << "Failed to load music for stage " << stage << "\n";
    }
    else {
        stageMusic.setLoop(true);
        stageMusic.setVolume(50);
        stageMusic.play();
    }
}

void PlayScreen::handleEvent(const sf::Event& event) {
    //player.handleInput();
}

void PlayScreen::update(float dt) {
    
    player.handleInput(dt);
    // --- Collision detection ---
    sf::FloatRect playerBounds = player.getGlobalBounds();
    for (const auto& wall : walls) {
        if (playerBounds.intersects(wall.getBounds())) {
            // Simple collision response: move player back
            player.revertMovement();
        }
    }

    // Enemy movement toward player
    enemy.updateAI(dt, player.getPosition());
}
void PlayScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(player);
    window.draw(enemy);
    for (const auto& wall : walls) {
        wall.draw(window);
    }

}
