#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <random>
#include <optional>
#include "GameState.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

struct Game {
    sf::RenderWindow window;
    GameState currentState;
    
    // Gestione Texture
    sf::Texture playerTex;
    sf::Texture enemyTex;
    
    Player player;
    std::vector<Bullet> bullets;
    
    std::vector<Enemy> enemies;
    sf::Clock enemySpawnClock;
    const sf::Time spawnRate;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> sideDist;
    std::uniform_real_distribution<float> xDist;
    std::uniform_real_distribution<float> yDist;

    int score;
    int lives;

    Game();
    void run();
    void loadResources();
    void processEvents();
    void update();
    void render();
    void shootBullet();
    void updateBullets();
    void spawnEnemy();
    void updateEnemies();
    void handleCollisions();
};