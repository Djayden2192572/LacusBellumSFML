#include "Enemy.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Enemy::Enemy() {
    m_texture.loadFromFile("ben.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.3f, 0.3f);
    sf::FloatRect lb = m_sprite.getLocalBounds();
    m_sprite.setOrigin(lb.width * 0.5f, lb.height * 0.5f);
    m_sprite.setPosition(1650, 900);
    m_speed = 15.f;
}

void Enemy::updateAI(float dt, sf::Vector2f playerPos) {
    shootTimer += dt;
    changeDirTimer += dt;

    // Randomly change direction
    if (changeDirTimer >= changeDirCooldown) {
        changeDirTimer = 0.f;
        float angle = (std::rand() % 360) * 3.14159f / 180.f;
        moveDirection = sf::Vector2f(std::cos(angle), std::sin(angle));
    }

    // Blend random movement with chasing player
    sf::Vector2f toPlayer = playerPos - m_sprite.getPosition();
    float len = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    if (len != 0) toPlayer /= len;

    sf::Vector2f finalDir = (toPlayer * 0.7f) + (moveDirection * 0.3f);
    len = std::sqrt(finalDir.x * finalDir.x + finalDir.y * finalDir.y);
    if (len != 0) finalDir /= len;

    m_sprite.move(finalDir * m_speed * dt);

    // Shoot
    if (shootTimer >= shootCooldown) {
        shootTimer = 0.f;
        shoot(playerPos);
    }

    // Update projectiles
    for (auto& proj : m_projectiles)
        proj.update(dt);

    // Remove dead projectiles
    m_projectiles.erase(
        std::remove_if(m_projectiles.begin(), m_projectiles.end(),
            [](const Projectile& p) { return !p.isAlive(); }),
        m_projectiles.end()
    );
}

void Enemy::shoot(sf::Vector2f targetPos) {
    sf::Vector2f direction = targetPos - m_sprite.getPosition();
    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (len != 0) direction /= len;

    sf::Vector2f velocity = direction * 100.f; // bullet speed
    Projectile p(m_sprite.getPosition(), velocity);
    p.setColor(sf::Color::Red); // ? use the new setter
    m_projectiles.push_back(p);

}

void Enemy::undoMove() {
    float angleRad = m_sprite.getRotation() * 3.14159265f / 180.f;
    m_sprite.move(-std::cos(angleRad) * m_speed * 0.016f,
        -std::sin(angleRad) * m_speed * 0.016f);
}

void Enemy::updateProjectiles(float dt, const std::vector<sf::RectangleShape>& walls) {
    for (auto& proj : m_projectiles) {
        proj.update(dt, &walls);  // ? pass walls here
    }
    // Remove dead projectiles
    m_projectiles.erase(
        std::remove_if(m_projectiles.begin(), m_projectiles.end(),
            [](Projectile& p) { return !p.isAlive(); }),
        m_projectiles.end()
    );
}

sf::FloatRect Enemy::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    for (const auto& proj : m_projectiles)
        target.draw(proj, states);
}
