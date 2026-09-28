#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

enum class PowerUpType { Spread, Shield };

struct PowerUp {
    sf::Sprite shape;
    PowerUpType type;

    PowerUp(const sf::Texture& texture, PowerUpType t);
};