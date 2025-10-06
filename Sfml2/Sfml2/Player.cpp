#include "Player.h"

Player::Player() {
    m_texture.loadFromFile("Alexio.png"); // Use a player-specific texture
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.3f, 0.3f);
    m_sprite.setPosition(400, 400); // Example start position
}

void Player::handleInput() {
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += m_speed;

    m_sprite.move(movement * 0.016f); // Replace with dt if available

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_timeSinceLastShot >= m_shootCooldown) {
        shoot();
        m_timeSinceLastShot = 0.f;
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    // Optionally draw projectiles here if managed by Player
}