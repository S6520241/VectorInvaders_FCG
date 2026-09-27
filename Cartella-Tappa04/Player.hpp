#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

struct Player {
    sf::RectangleShape shape;

    void init();
    void reset();
    void updateMovement(float speed);
    void updateRotation(const sf::RenderWindow& window);
    void constrainBounds(float windowWidth, float windowHeight);
};