#include "Enemy.hpp"

Enemy::Enemy(const sf::Texture& texture, EnemyType t, int health) 
    : shape(texture), type(t), hp(health) {
}