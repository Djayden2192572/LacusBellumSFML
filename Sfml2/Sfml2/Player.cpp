#include "Player.h"
#include "iostream"
Player::Player() {
    m_texture.loadFromFile("Alexio.png"); // Use a player-specific texture
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.3f, 0.3f);
    m_sprite.setPosition(300, 300); // Example start position
}

void Player::handleInput() {
    sf::Vector2f movement(0.f, 0.f);
    std::cout << "handleInput called\n";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= m_speed;
        std::cout << "W pressed\n";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += m_speed;
        std::cout << "S pressed\n";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= m_speed;
        std::cout << "A pressed\n";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += m_speed;
        std::cout << "D pressed\n";
    }

    m_sprite.move(movement * 0.016f); // Replace with dt if available

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_timeSinceLastShot >= m_shootCooldown) {
        std::cout << "Space pressed - shooting\n";
        shoot();
        m_timeSinceLastShot = 0.f;
    }
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    // Optionally draw projectiles here if managed by Player
}