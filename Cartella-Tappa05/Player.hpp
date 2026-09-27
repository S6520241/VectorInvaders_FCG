#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

struct Player {
    sf::Sprite shape;

    // Costruttore obbligatorio per l'inizializzazione dello Sprite in SFML 3.0
    Player(const sf::Texture& texture);

    void init(const sf::Texture& texture, float targetSize, float startX, float startY);
    void reset(float startX, float startY);
    void updateMovement(float speed);
    void updateRotation(const sf::RenderWindow& window);
    void constrainBounds(float windowWidth, float windowHeight);
};