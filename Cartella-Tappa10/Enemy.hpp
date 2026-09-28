#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

// Enum per i nuovi tipi di nemici
enum class EnemyType { Base, Tank, Shooter };

struct Enemy {
    sf::Sprite shape;
    EnemyType type;
    int hp;
    sf::Clock shootClock;
    
    // Costruttore aggiornato per inizializzare le nuove caratteristiche
    Enemy(const sf::Texture& texture, EnemyType t, int health);
};