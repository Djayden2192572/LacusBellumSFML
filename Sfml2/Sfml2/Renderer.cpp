#include "Renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode(width, height), title), shape(100.f)
{
    shape.setFillColor(sf::Color::Green);
    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        
    }

    // Set up title text
    titleText.setFont(font);
    titleText.setString("Press Enter to Start");
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(200, 350);

    // Load background image
    if (!backgroundTexture.loadFromFile("background.png.png")) {
        
    }
    backgroundSprite.setTexture(backgroundTexture);

}


void Renderer::run() {
    bool showTitle = true;

    // Scale background to fit 1920x1080
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                showTitle = false;
        }

        window.clear();

        // Draw background image
        window.draw(backgroundSprite);

        if (showTitle) {
            window.draw(titleText);
        }
        else {
            window.draw(shape);
        }

        window.display();
    }
}
