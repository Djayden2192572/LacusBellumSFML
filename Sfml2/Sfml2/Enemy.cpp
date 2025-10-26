#include "Enemy.h"

Enemy::Enemy() {
    m_texture.loadFromFile("ben.png"); // Use an enemy-specific texture
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.3f, 0.3f);
    sf::FloatRect lb = m_sprite.getLocalBounds();
    m_sprite.setOrigin(lb.width * 0.5f, lb.height * 0.5f);
    m_sprite.setPosition(1650, 900); // Example start position
    m_speed = 00.f; 
}

void Enemy::updateAI(float dt, sf::Vector2f playerPos) {
    sf::Vector2f direction = playerPos - m_sprite.getPosition();

    // Normalize direction
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    // Move toward player
    m_sprite.move(direction * m_speed * dt);
}


void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    // Optionally draw projectiles here if managed by Enemy
}