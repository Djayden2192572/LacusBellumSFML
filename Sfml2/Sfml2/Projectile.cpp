#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, float lifetime)
    : m_velocity(velocity), m_lifetime(lifetime), m_age(0.0f), m_alive(true)
{
    m_shape.setRadius(5.0f);
    m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius()); // center origin
    m_shape.setFillColor(sf::Color::Black);
    m_shape.setPosition(position);
}

void Projectile::update(float dt, const std::vector<sf::RectangleShape>* walls)
{
    if (!m_alive) return;

    m_shape.move(m_velocity * dt);
    m_age += dt;

    // Simple AABB test between projectile's global bounds and each wall.
    if (walls) {
        for (const auto& wall : *walls) {
            if (m_shape.getGlobalBounds().intersects(wall.getGlobalBounds())) {
                m_alive = false;
                break;
            }
        }
    }
}

bool Projectile::isAlive() const {
    return m_alive && (m_age < m_lifetime);
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (m_alive) target.draw(m_shape, states);
}