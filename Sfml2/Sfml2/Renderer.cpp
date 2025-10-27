#include "Renderer.h"
#include <iostream>
#include "Player.h"
#include "PlayScreen.h"
#include <algorithm>

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
    // playscreen title bg
    if (!gameplayBackgroundTexture.loadFromFile("GameBG.png")) {
        std::cerr << "Failed to load gameplay background\n";
    }
    gameplayBackgroundSprite.setTexture(gameplayBackgroundTexture);
    gameplayBackgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / gameplayBackgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / gameplayBackgroundTexture.getSize().y
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

    // Load game-over images (optional — fallback to text if missing)
    // Load game-over images the same way as MainMenu (file must be next to the exe / working dir)
    gameOverWinLoaded = gameOverWinTexture.loadFromFile("Vicroyy.png");
    if (!gameOverWinLoaded) {
        std::cerr << "Failed to load game over win image: Vicroyy.png\n";
    }
    gameOverWinSprite.setTexture(gameOverWinTexture);
    gameOverWinSprite.setScale(
        static_cast<float>(window.getSize().x) / gameOverWinTexture.getSize().x,
        static_cast<float>(window.getSize().y) / gameOverWinTexture.getSize().y
    );

    gameOverLoseLoaded = gameOverLoseTexture.loadFromFile("visitor.png");
    if (!gameOverLoseLoaded) {
        std::cerr << "Failed to load game over lose image: visitor.png\n";
    }
    gameOverLoseSprite.setTexture(gameOverLoseTexture);
    gameOverLoseSprite.setScale(
        static_cast<float>(window.getSize().x) / gameOverLoseTexture.getSize().x,
        static_cast<float>(window.getSize().y) / gameOverLoseTexture.getSize().y
    );
    if (!gameOverMusic.openFromFile("Assets/audio/gameover.wav")) {
    std::cerr << "Failed to load game over music\n";
}
if (!victoryMusic.openFromFile("Assets/audio/victory.wav")) {
    std::cerr << "Failed to load victory music\n";
}

}

void Renderer::run() {
    bool showTitle = true;
    bool startGame = false;
    bool openCodes = false;
    bool quitGame = false;
    bool inGame = false;
    sf::Clock clock;


    // Game-over UI state
    bool showGameOver = false;
    bool playerWon = false;
    sf::Text gameOverText;
    sf::Text restartText;
    sf::Text menuText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(2.f);

    restartText.setFont(font);
    restartText.setCharacterSize(36);
    restartText.setFillColor(sf::Color::White);
    restartText.setOutlineColor(sf::Color::Black);
    restartText.setOutlineThickness(2.f);

    menuText.setFont(font);
    menuText.setCharacterSize(36);
    menuText.setFillColor(sf::Color::White);
    menuText.setOutlineColor(sf::Color::Black);
    menuText.setOutlineThickness(2.f);

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // If the game over overlay is active, handle clicks on its buttons
            if (showGameOver && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (restartText.getGlobalBounds().contains(mousePos)) {
                    showGameOver = false;
                    inGame = true;
                    playScreen = std::make_unique<PlayScreen>(window.getSize(), 1);
                    victoryMusic.stop();
                    gameOverMusic.stop();
                }
                else if (menuText.getGlobalBounds().contains(mousePos)) {
                    showGameOver = false;
                    inGame = false;
                    isMainMenu = true;
                    mainMenu = std::make_unique<MainMenu>(window.getSize());
                    victoryMusic.stop();
                    gameOverMusic.stop();
                    backgroundMusic.play();
                }
            }


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
            playScreen = std::make_unique<PlayScreen>(window.getSize(), 1);
            startGame = false;
            backgroundMusic.stop();
        }

        // Update gameplay (only while inGame)
        if (inGame && playScreen) {
            playScreen->update(dt);
            // If playScreen reports a result, show game-over overlay and stop being "inGame"
            auto result = playScreen->getResult();
            if (result != PlayScreen::Result::None) {
                showGameOver = true;
                playerWon = (result == PlayScreen::Result::EnemyDead); // enemy dead => player won
                inGame = false; // drop out of gameplay updates; keep playScreen alive for drawing final frame
                if (playerWon) {
                    victoryMusic.play();
                }
                else {
                    gameOverMusic.play();
                }
            }
        }

        window.clear();

        if (inGame && playScreen) {
            // --- GAME SCREEN START ---
            window.draw(gameplayBackgroundSprite);
            playScreen->draw(window);
            // --- GAME SCREEN END ---
        }
        else if (showGameOver && playScreen) {
            // draw final gameplay frame under overlay
            window.draw(gameplayBackgroundSprite);
            playScreen->draw(window);

            // Draw overlay background
            sf::RectangleShape overlay;
            overlay.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
            overlay.setFillColor(sf::Color(0, 0, 0, 160));
            window.draw(overlay);

            // Draw image (win/lose) if loaded, else fallback to text
            if (playerWon && gameOverWinLoaded) {
                window.draw(gameOverWinSprite);
            } else if (!playerWon && gameOverLoseLoaded) {
                window.draw(gameOverLoseSprite);
            } else {
                if (playerWon) gameOverText.setString("You Win!");
                else gameOverText.setString("You Died!");

                // center gameOverText
                sf::FloatRect goBounds = gameOverText.getLocalBounds();
                gameOverText.setOrigin(goBounds.left + goBounds.width / 2.f, goBounds.top + goBounds.height / 2.f);
                gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 80.f);
                window.draw(gameOverText);
            }

            // restart button
            restartText.setString("Restart");
            sf::FloatRect rBounds = restartText.getLocalBounds();
            restartText.setOrigin(rBounds.left + rBounds.width / 2.f, rBounds.top + rBounds.height / 2.f);
            restartText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 10.f);
            window.draw(restartText);

            // main menu button
            menuText.setString("Main Menu");
            sf::FloatRect mBounds = menuText.getLocalBounds();
            menuText.setOrigin(mBounds.left + mBounds.width / 2.f, mBounds.top + mBounds.height / 2.f);
            menuText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 70.f);
            window.draw(menuText);
        }
        else if (isMainMenu && mainMenu) {
            mainMenu->draw(window);
        }
        else {
            // Title screen
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
