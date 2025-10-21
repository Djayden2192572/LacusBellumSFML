#include "Playscreen.h"
#include <iostream>


PlayScreen::PlayScreen(sf::Vector2u windowSize, int stageNumber) : stage(stageNumber) {
    std::string bgPath = "Assets/images/stage" + std::to_string(stage) + "GameBG.png";
    std::string musicPath = "Assets/audio/stage" + std::to_string(stage) + "_theme.wav";

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
    std::cout << "PlayScreen update running\n"; // Debug
    // Process input that may fire projectiles / move the player
    player.handleInput(dt);

    // IMPORTANT: update the player so character::update runs (projectiles move, lifetime, cooldown)
    player.update(dt);

    // Enemy movement toward player
    enemy.updateAI(dt, player.getPosition());
}
void PlayScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(player);
    window.draw(enemy);
}
