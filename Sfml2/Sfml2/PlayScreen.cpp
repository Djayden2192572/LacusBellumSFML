#include "PlayScreen.h"
#include <iostream>

PlayScreen::PlayScreen(sf::Vector2u windowSize, int stageNumber) : stage(stageNumber) {
    
    std::string musicPath = "Assets/audio/stage" + std::to_string(stage) + "_theme.wav";
    if (!stageMusic.openFromFile(musicPath)) {
        std::cerr << "Failed to load stage music\n";
    }
    stageMusic.setLoop(true);
    stageMusic.play();

    if (!pauseMusic.openFromFile("Assets/audio/pause_theme.wav")) {
        std::cerr << "Failed to load pause music\n";
    }
    pauseMusic.setLoop(true);

    sf::RectangleShape wall1(sf::Vector2f(1700, 40));
    wall1.setPosition(100, 1000);
    wall1.setFillColor(sf::Color(200, 200, 220, 200));
    walls.push_back(wall1);

    sf::RectangleShape wall2(sf::Vector2f(1700, 40));
    wall2.setPosition(100, 99);
    wall2.setFillColor(sf::Color(200, 200, 220, 200));
    walls.push_back(wall2);

    sf::RectangleShape wall3(sf::Vector2f(40, 1000));
    wall3.setPosition(100, 30);
    wall3.setFillColor(sf::Color(200, 200, 220, 200));
    walls.push_back(wall3);

    sf::RectangleShape wall4(sf::Vector2f(40, 1000));
    wall4.setPosition(1750, 30);
    wall4.setFillColor(sf::Color(200, 200, 220, 200));
    walls.push_back(wall4);

    sf::RectangleShape wall5(sf::Vector2f(70, 495));
    wall5.setPosition(400, 335);
    wall5.setFillColor(sf::Color(200, 200, 220, 200));
    walls.push_back(wall5);

    sf::RectangleShape wall6(sf::Vector2f(90, 495));
    wall6.setPosition(480, 335);
    wall6.setFillColor(sf::Color(200, 200, 220, 200));
    walls.push_back(wall6);

    sf::RectangleShape wall7(sf::Vector2f(70, 495));
    wall7.setPosition(1300, 335);
    wall7.setFillColor(sf::Color(200, 200, 220, 200)); // Fully transparent first number = fat, 2= height, 3 = y, 4 = X
	walls.push_back(wall7);                    // 200, 200, 220, 200 for testing

    sf::RectangleShape wall8(sf::Vector2f(480, 80));
    wall8.setPosition(1100, 550);
    wall8.setFillColor(sf::Color(200, 200, 220, 200));
    walls.push_back(wall8);
   
    if (!reggaeFont.loadFromFile("Assets/fonts/ReggaeOne.ttf")) {
        std::cerr << "Failed to load ReggaeOne font\n";
    }


    

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
        static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
    );

    }


void PlayScreen::handleEvent(const sf::Event& event) {}

void PlayScreen::update(float dt) {
    

    // First update characters so timers & existing projectiles advance
    player.update(dt, &walls);
    enemy.update(dt, &walls);
    
    
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        isPaused = !isPaused;
        sf::sleep(sf::milliseconds(200)); // debounce

        if (isPaused) {
            stageMusic.pause();
            pauseMusic.play();
        }
        else {
            pauseMusic.stop();
            stageMusic.play();
        }
    }

    if (isPaused) return; // skip movement, enemy logic, etc.




    // Then process input/AI (they may spawn new projectiles that will be updated next frame)
    player.handleInput(dt, walls);
    enemy.updateAI(dt, player.getPosition());
}

void PlayScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (const auto& wall : walls)
        window.draw(wall);

    if (isPaused) {
        sf::Text pauseText;
        pauseText.setFont(reggaeFont); // make sure you’ve loaded a font
        pauseText.setString("Paused");
        pauseText.setCharacterSize(70);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setPosition(750.f, 540.f); // center it
        sf::RectangleShape overlay;
        overlay.setSize(sf::Vector2f(1920.f, 1080.f));
        overlay.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent black

        window.draw(overlay);

        window.draw(pauseText);
    }


    window.draw(player);
    window.draw(enemy);
}
