#include "Player.h"
#include "iostream"
Player::Player() {
    m_texture.loadFromFile("Alexio.png"); // Use a player-specific texture
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.3f, 0.3f);
    m_sprite.setPosition(300, 300); // Example start position

}

void Player::handleInput(float dt) {
    float rotationSpeed = 120.f; // degrees per second
    float moveSpeed = m_speed;   // units per second

    // Handle rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_sprite.rotate(-rotationSpeed * dt); // Turn left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_sprite.rotate(rotationSpeed * dt);  // Turn right
    }

    // Handle forward/backward movement
    sf::Vector2f movement(0.f, 0.f);
    float angleRad = m_sprite.getRotation() * 3.14159265f / 180.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.x += std::cos(angleRad) * moveSpeed * dt;
        movement.y += std::sin(angleRad) * moveSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.x -= std::cos(angleRad) * moveSpeed * dt;
        movement.y -= std::sin(angleRad) * moveSpeed * dt;
    }

    m_sprite.move(movement);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_timeSinceLastShot >= m_shootCooldown) {
        shoot();
        m_timeSinceLastShot = 0.f;
    }
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    // Optionally draw projectiles here if managed by Player
   
}
sf::Vector2f Player::getPosition() const {
    ;
    return m_sprite.getPosition();

}