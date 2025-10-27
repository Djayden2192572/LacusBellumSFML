#include "Player.h"
#include <cmath>
#include <algorithm>

Player::Player() {
    m_texture.loadFromFile("Alexio.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.2f, 0.2f);

    // Important: center the origin so m_sprite.getPosition() is the visual center
    sf::FloatRect lb = m_sprite.getLocalBounds();
    m_sprite.setOrigin(lb.width * 0.5f, lb.height * 0.5f);

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

    // Compute circular hitbox radius (based on sprite local bounds and scale)
    sf::FloatRect lb = m_sprite.getLocalBounds();
    float radius = std::max(lb.width * m_sprite.getScale().x, lb.height * m_sprite.getScale().y) * 0.5f;

    // Target center after applying movement
    sf::Vector2f newCenter = m_sprite.getPosition() + movement;

    // Closest-point (clamp) circle-vs-AABB test
    auto circleIntersectsRect = [](const sf::Vector2f& center, float r, const sf::FloatRect& rect) {
        float closestX = std::clamp(center.x, rect.left, rect.left + rect.width);
        float closestY = std::clamp(center.y, rect.top, rect.top + rect.height);
        float dx = center.x - closestX;
        float dy = center.y - closestY;
        return (dx*dx + dy*dy) < (r*r);
    };

    bool collision = false;
    for (const auto& wall : walls) {
        if (circleIntersectsRect(newCenter, radius, wall.getGlobalBounds())) {
            collision = true;
            break;
        }
    }

    if (!collision) {
        m_sprite.move(movement);
        m_lastMovement = movement;
    } else {
        m_lastMovement = {0.f, 0.f};
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_timeSinceLastShot >= m_shootCooldown) {
        shoot();
        m_timeSinceLastShot = -1.f;
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
    // projectiles are drawn in Character::draw
    Character::draw(target, states);
}
