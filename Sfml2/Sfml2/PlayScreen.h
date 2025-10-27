#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class PlayScreen {
public:
    enum class Result { None, PlayerDead, EnemyDead };

    PlayScreen(sf::Vector2u windowSize, int stageNumber);
    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    // Query result (None while playing)
    Result getResult() const { return m_result; }

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music stageMusic;
    sf::Music pauseMusic;
    bool isPaused = false;
    sf::Font reggaeFont;
    Player player;
    Enemy enemy;
    int stage;

    std::vector<sf::RectangleShape> walls;

    Result m_result = Result::None;
};
