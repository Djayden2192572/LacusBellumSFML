#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"

class Enemy : public sf::Drawable {
public:
    Enemy();
    void updateAI(float dt, sf::Vector2f playerPos);
    sf::FloatRect getGlobalBounds() const;
    void undoMove();
    void updateProjectiles(float dt, const std::vector<sf::RectangleShape>& walls);
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void shoot(sf::Vector2f targetPos);

    sf::Texture m_texture;
    sf::Sprite m_sprite;
    float m_speed = 120.f;

    // AI timers
    float shootTimer = 0.f;
    float shootCooldown = 1.5f;
    float changeDirTimer = 0.f;
    float changeDirCooldown = 3.f;
    sf::Vector2f moveDirection;

    // Projectiles
    std::vector<Projectile> m_projectiles;
};
