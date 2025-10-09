#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>

class Player : public Character {
public:
    Player();

    void handleInput(); // Player-specific input

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};