#include "Game.h"
#include <SFML/OpenGL.hpp>

Game::Game()
    : m_vertices(sf::Triangles, 3)
{
    // Example initialization
    m_texture.loadFromFile("example.png");
    m_sprite.setTexture(m_texture);

    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(100, 0);
    m_vertices[2].position = sf::Vector2f(100, 100);
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw high-level objects
    target.draw(m_sprite, states);

    // Draw using low-level API
    states.texture = &m_texture;
    target.draw(m_vertices, states);

    // Draw with OpenGL directly
    glBegin(GL_TRIANGLES);
    // Example OpenGL drawing (replace with your own vertices/colors)
    glVertex2f(0.f, 0.f);
    glVertex2f(100.f, 0.f);
    glVertex2f(100.f, 100.f);
    glEnd();
}