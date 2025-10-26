#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, float lifetime)
    : m_velocity(velocity), m_lifetime(lifetime), m_age(0.0f)
{
    m_shape.setRadius(10.0f);
    m_shape.setFillColor(sf::Color::Black);
    m_shape.setPosition(position);
}

void Projectile::update(float dt) {
    m_shape.move(m_velocity * dt);
    m_age += dt;
}

bool Projectile::isAlive() const {
    return m_age < m_lifetime;
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}