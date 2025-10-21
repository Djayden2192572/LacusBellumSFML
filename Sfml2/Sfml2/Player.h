#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>

class Player : public Character {
public:
    Player();

    void handleInput(float dt, const std::vector<sf::RectangleShape>& walls); // Player-specific input
    sf::Vector2f getPosition() const; // Returns player's current position
    sf::FloatRect getGlobalBounds() const;
    void undoMove();

    // store last movement so we can rollback exactly
    sf::Vector2f m_lastMovement;


protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};