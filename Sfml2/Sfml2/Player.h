#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>

class Player : public Character {
public:
    Player();

    void handleInput(float dt); // Player-specific input
    sf::Vector2f getPosition() const; // Returns player's current position

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};