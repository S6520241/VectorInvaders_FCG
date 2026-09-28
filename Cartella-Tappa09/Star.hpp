#pragma once
#include <SFML/Graphics/CircleShape.hpp>

struct Star {
    sf::CircleShape shape;
    float speed;

    Star() = default;
};