#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

struct Particle {
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float lifetime;
    float maxLifetime;

    Particle() = default;
};