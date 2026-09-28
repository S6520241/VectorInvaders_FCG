#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

// Struttura per gestire ogni singolo proiettile
struct Bullet {
    sf::RectangleShape shape;
    sf::Vector2f velocity; 
};