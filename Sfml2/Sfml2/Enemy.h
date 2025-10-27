#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>

class Enemy : public Character {
public:
    Enemy();
    void updateAI(float dt, sf::Vector2f playerPos);
    sf::FloatRect getGlobalBounds() const;
    void undoMove();
    void updateProjectiles(float dt, const std::vector<sf::RectangleShape>& walls);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void shoot(sf::Vector2f targetPos); // <- add this

    float m_speed = 120.f;

    // AI timers
    float shootTimer = 0.f;
    float shootCooldown = 1.5f;
    float changeDirTimer = 0.f;
    float changeDirCooldown = 3.f;
    sf::Vector2f moveDirection;

    // NOTE: no m_projectiles here anymore — use Character::m_projectiles
};
