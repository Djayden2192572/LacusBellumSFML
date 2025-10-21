#include "Player.h"
#include <cmath>

Player::Player() {
    m_texture.loadFromFile("Alexio.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.3f, 0.3f);
    m_sprite.setPosition(300, 300);
}

void Player::handleInput(float dt, const std::vector<sf::RectangleShape>& walls) {
    float rotationSpeed = 120.f;
    float moveSpeed = m_speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_sprite.rotate(-rotationSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_sprite.rotate(rotationSpeed * dt);

    sf::Vector2f movement(0.f, 0);
    float angleRad = m_sprite.getRotation() * 3.14159265f / 180.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.x += std::cos(angleRad) * moveSpeed * dt;
        movement.y += std::sin(angleRad) * moveSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.x -= std::cos(angleRad) * moveSpeed * dt;
        movement.y -= std::sin(angleRad) * moveSpeed * dt;
    }

    // Predict next position
    sf::Sprite temp = m_sprite;
    temp.move(movement);

    bool collision = false;
    for (const auto& wall : walls) {
        if (temp.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            collision = true;
            break;
        }
    }

    if (!collision)
        m_sprite.move(movement);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_timeSinceLastShot >= m_shootCooldown) {
        shoot();
        m_timeSinceLastShot = 0.f;
    }
}

sf::Vector2f Player::getPosition() const {
    return m_sprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
