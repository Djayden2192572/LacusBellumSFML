#include "PlayScreen.h"
#include <iostream>

PlayScreen::PlayScreen(sf::Vector2u windowSize, int stageNumber) : stage(stageNumber) {
    std::string bgPath = "Assets/images/stage" + std::to_string(stage) + "GameBG.png";
    std::string musicPath = "Assets/audio/stage" + std::to_string(stage) + "_theme.wav";

    sf::RectangleShape wall1(sf::Vector2f(1700, 40));
    wall1.setPosition(100, 1000);
    wall1.setFillColor(sf::Color(0, 0, 0, 0)); // Fully transparent
    walls.push_back(wall1);

    sf::RectangleShape wall2(sf::Vector2f(1700, 40));
    wall2.setPosition(100, 99);
    wall2.setFillColor(sf::Color(0, 0, 0, 0)); // Fully transparent
    walls.push_back(wall2);

    sf::RectangleShape wall3(sf::Vector2f(40, 1000));
    wall3.setPosition(100, 30);
    wall3.setFillColor(sf::Color(0, 0, 0, 0)); // Fully transparent
    walls.push_back(wall3);

    sf::RectangleShape wall4(sf::Vector2f(40, 1000));
    wall4.setPosition(1750, 30);
    wall4.setFillColor(sf::Color(0, 0, 0, 0)); // Fully transparent
    walls.push_back(wall4);


    if (!backgroundTexture.loadFromFile(bgPath))
        std::cerr << "Failed to load background for stage " << stage << "\n";

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
        static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
    );

    if (!stageMusic.openFromFile(musicPath))
        std::cerr << "Failed to load music for stage " << stage << "\n";
    else {
        stageMusic.setLoop(true);
        stageMusic.setVolume(50);
        stageMusic.play();
    }
}

void PlayScreen::handleEvent(const sf::Event& event) {}

void PlayScreen::update(float dt) {
    player.handleInput(dt, walls);
    enemy.updateAI(dt, player.getPosition()); // enemy still free to pass through walls
}

void PlayScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (const auto& wall : walls)
        window.draw(wall);

    window.draw(player);
    window.draw(enemy);
}
