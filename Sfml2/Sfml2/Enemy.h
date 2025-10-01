#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>

class Enemy : public Character {
public:
    Enemy();

    void updateAI(float dt); // Enemy-specific AI logic

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
};