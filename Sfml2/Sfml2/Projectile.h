#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Projectile : public sf::Drawable {
public:
    Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, float lifetime = 4.0f);

    // If walls == nullptr, no wall-checking is performed.
    void update(float dt, const std::vector<sf::RectangleShape>* walls = nullptr);
    bool isAlive() const;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
    float m_lifetime;
    float m_age;
    bool m_alive;
};