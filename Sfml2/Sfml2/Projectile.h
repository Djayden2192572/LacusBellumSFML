#pragma once
#include <SFML/Graphics.hpp>

class Projectile : public sf::Drawable {
public:
    Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, float lifetime = 2.0f);

    void update(float dt);
    bool isAlive() const;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
    float m_lifetime;
    float m_age;
};