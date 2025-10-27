#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"

class Projectile; // Forward declaration if you have a Projectile class

class Character : public sf::Drawable {
public:
    Character();

    void handleInput();      // For movement and shooting (if player-controlled)
    // Updated: pass optional pointer to walls (nullptr = none)
    void update(float dt, const std::vector<sf::RectangleShape>* walls = nullptr);   // For updating position, projectiles, etc.
    void takeDamage(int amount);
    int getHP() const;

    // expose projectiles so PlayScreen can test collisions
    std::vector<Projectile>& getProjectiles() { return m_projectiles; }
    const std::vector<Projectile>& getProjectiles() const { return m_projectiles; }

protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::vector<Projectile> m_projectiles;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    int m_hp;
    float m_speed;

    float m_shootCooldown;
    float m_timeSinceLastShot;

    void shoot();
};