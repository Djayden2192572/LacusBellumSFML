#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Projectile; // Forward declaration if you have a Projectile class

class Character : public sf::Drawable {
public:
    Character();

    void handleInput();      // For movement and shooting (if player-controlled)
    void update(float dt);   // For updating position, projectiles, etc.
    void takeDamage(int amount);
    int getHP() const;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite m_sprite;
    sf::Texture m_texture;
    int m_hp;
    float m_speed;

    //std::vector<Projectile> m_projectiles; // If you have a projectile class
    float m_shootCooldown;
    float m_timeSinceLastShot;

    void shoot();
};