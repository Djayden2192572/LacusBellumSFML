#include "Character.h"
#include "Projectile.h" // If you have a Projectile class
#include "iostream"

Character::Character()
    : m_hp(100), m_speed(200.f), m_shootCooldown(0.5f), m_timeSinceLastShot(0.f)
{
    m_texture.loadFromFile("Alexio.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(400, 400); // Example start position
    m_sprite.setOrigin(
        m_texture.getSize().x / 2.f,
        m_texture.getSize().y / 2.f
        );
    
}



void Character::update(float dt) {
    m_timeSinceLastShot += dt;
    for (auto& proj : m_projectiles) proj.update(dt);
    m_projectiles.erase(
       std::remove_if(m_projectiles.begin(), m_projectiles.end(),
                      [](const Projectile& p) { return !p.isAlive(); }),
       m_projectiles.end());
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
    std::cout << "Shooting!\n";
    float angle = m_sprite.getRotation() * 3.14159265f / 180.f;
    sf::Vector2f direction(std::cos(angle), std::sin(angle));
    float speed = 400.f; // Adjust as needed
    m_projectiles.emplace_back(m_sprite.getPosition(), direction * speed);
 
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    for (const auto& proj : m_projectiles) target.draw(proj, states);
    // Draw projectiles if you have them
}