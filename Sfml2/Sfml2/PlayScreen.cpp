#include "PlayScreen.h"
#include <iostream>

PlayScreen::PlayScreen(sf::Vector2u windowSize, int stageNumber) : stage(stageNumber) {
    
    std::string musicPath = "Assets/audio/stage" + std::to_string(stage) + "_theme.wav";

    sf::RectangleShape wall1(sf::Vector2f(1700, 40));
    wall1.setPosition(100, 1000);
    wall1.setFillColor(sf::Color(0, 0, 0, 0)); 
    walls.push_back(wall1);

    sf::RectangleShape wall2(sf::Vector2f(1700, 40));
    wall2.setPosition(100, 99);
    wall2.setFillColor(sf::Color(0, 0, 0, 0)); 
    walls.push_back(wall2);

    sf::RectangleShape wall3(sf::Vector2f(40, 1000));
    wall3.setPosition(100, 30);
    wall3.setFillColor(sf::Color(0, 0, 0, 0)); 
    walls.push_back(wall3);

    sf::RectangleShape wall4(sf::Vector2f(40, 1000));
    wall4.setPosition(1750, 30);
    wall4.setFillColor(sf::Color(0, 0, 0, 0)); 
    walls.push_back(wall4);

    sf::RectangleShape wall5(sf::Vector2f(70, 495));
    wall5.setPosition(400, 335);
    wall5.setFillColor(sf::Color(200, 200, 220, 200)); 
    walls.push_back(wall5);

    sf::RectangleShape wall6(sf::Vector2f(90, 495));
    wall6.setPosition(480, 335);
    wall6.setFillColor(sf::Color(0, 0, 0, 0)); 
    walls.push_back(wall6);

    sf::RectangleShape wall7(sf::Vector2f(70, 495));
    wall7.setPosition(1300, 335);
    wall7.setFillColor(sf::Color(0, 0, 0, 0)); // Fully transparent first number = fat, 2= height, 3 = y, 4 = X
    walls.push_back(wall7);

    sf::RectangleShape wall8(sf::Vector2f(480, 80));
    wall8.setPosition(1100, 550);
    wall8.setFillColor(sf::Color(0, 0, 0, 0)); 
    walls.push_back(wall8);
   

    

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
