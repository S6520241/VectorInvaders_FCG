#pragma once
#include <SFML/Graphics.hpp>

struct Player {
    sf::RectangleShape shape;
    const float speed = 5.0f;

    Player();
    void resetPosition();
    void update();
};