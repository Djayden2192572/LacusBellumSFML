#include "Character.h"
#include "Projectile.h" // If you have a Projectile class

Character::Character()
    : m_hp(100), m_speed(200.f), m_shootCooldown(0.5f), m_timeSinceLastShot(0.f)
{
    m_texture.loadFromFile("character.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(400, 400); // Example start position
}



void Character::update(float dt) {
    m_timeSinceLastShot += dt;
    // Update projectiles, etc.
}

void Character::takeDamage(int amount) {
    m_hp -= amount;
    if (m_hp < 0) m_hp = 0;
}

int Character::getHP() const {
    return m_hp;
}

void Character::shoot() {
    // Add a new projectile to m_projectiles
    // Example: m_projectiles.push_back(Projectile(m_sprite.getPosition()));
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    // Draw projectiles if you have them
}