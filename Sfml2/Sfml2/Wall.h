#pragma once
#include <SFML/Graphics.hpp>

class Wall {
public:
    Wall(sf::Vector2f position, sf::Vector2f size) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color(100, 100, 100)); // Gray wall
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    const sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

private:
    sf::RectangleShape shape;
};
