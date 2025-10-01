#include "Enemy.h"

Enemy::Enemy() {
    m_texture.loadFromFile("enemy.png"); // Use an enemy-specific texture
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(200, 200); // Example start position
}

void Enemy::updateAI(float dt) {
    // Example AI: move downwards
    sf::Vector2f movement(0.f, m_speed * dt);
    m_sprite.move(movement);

    // Example shooting logic (could be timer-based)
    if (m_timeSinceLastShot >= m_shootCooldown) {
        shoot();
        m_timeSinceLastShot = 0.f;
    }
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    // Optionally draw projectiles here if managed by Enemy
}