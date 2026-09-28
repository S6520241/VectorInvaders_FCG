#include "PowerUp.hpp"

PowerUp::PowerUp(const sf::Texture& texture, PowerUpType t) 
    : shape(texture), type(t) {
}