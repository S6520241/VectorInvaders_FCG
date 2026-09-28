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
#include "PowerUp.hpp"
#include "Star.hpp"
#include "Particle.hpp"

struct Game {
    sf::RenderWindow window;
    GameState currentState;
    
    sf::Texture playerTex;
    sf::Texture enemyTex;
    sf::Texture tankTex;
    sf::Texture shooterTex;
    sf::Texture spreadTex;
    sf::Texture shieldTex;
    
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Enemy> enemies;
    std::vector<PowerUp> powerUps;
    
    // VFX - Variabili Screen Shake e Particelle
    std::vector<Particle> particles;
    std::vector<Star> stars;
    float shakeDuration;
    sf::View gameView;
    
    sf::Clock enemySpawnClock;
    const sf::Time spawnRate;
    
    sf::Clock powerUpSpawnClock;
    const sf::Time powerUpSpawnRate;
    
    bool hasSpread;
    sf::Clock spreadClock;
    
    bool hasShield;
    sf::CircleShape shieldVisual;
    
    bool isInvulnerable;
    sf::Clock invulnerabilityClock;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> typeDist;
    std::uniform_int_distribution<> sideDist;
    std::uniform_real_distribution<float> xDist;
    std::uniform_real_distribution<float> yDist;
    std::uniform_real_distribution<float> xFullDist;
    std::uniform_real_distribution<float> yFullDist;

    int score;
    int lives;

    Game();
    void run();
    void loadResources();
    void initStars();
    void processEvents();
    void update();
    void render();
    
    void shootBullet();
    void updateBullets();
    void spawnEnemy();
    void updateEnemies();
    void spawnPowerUp();
    void updatePowerUps();
    
    void spawnExplosion(sf::Vector2f pos, sf::Color color, int count);
    void updateVFX();
    void applyScreenShake();
    
    void handleCollisions();
    void takeDamage();
};