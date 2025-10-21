#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class PlayScreen {
public:
    PlayScreen(sf::Vector2u windowSize, int stageNumber);
    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music stageMusic;

    Player player;
    Enemy enemy;
    int stage;

    std::vector<sf::RectangleShape> walls;
};
