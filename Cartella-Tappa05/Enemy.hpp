#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct Enemy {
    sf::Sprite shape;
    
    // Costruttore: inizializza lo sprite usando la texture passata come argomento
    Enemy(const sf::Texture& texture);
};