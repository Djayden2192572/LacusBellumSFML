#pragma once
#include <SFML/Graphics.hpp>

class Game : public sf::Drawable {
public:
    Game();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
};