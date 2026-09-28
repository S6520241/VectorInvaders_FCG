#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <random>
#include <optional>
#include "GameState.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "PowerUp.hpp"
#include "Star.hpp"
#include "Particle.hpp"

struct Game {
    sf::RenderWindow window;
    GameState currentState;
    float survivalTime;

    // Risorse
    sf::Texture playerTex, enemyTex, tankTex, shooterTex, spreadTex, shieldTex;
    sf::Font font;

    // Interfaccia
    sf::Text hudText;
    sf::Text titleText;
    sf::RectangleShape startButton;
    sf::Text startText;
    sf::RectangleShape exitButtonMenu;
    sf::Text exitTextMenu;
    sf::Text promptText;

    sf::RectangleShape pauseOverlay;
    sf::Text pauseText;
    sf::RectangleShape menuButtonPause;
    sf::Text menuTextPause;
    sf::RectangleShape exitButtonPause;
    sf::Text exitTextPause;

    // Giocatore
    sf::Sprite player;
    float playerScale;
    float playerSpeed;

    // Proiettili
    std::vector<Bullet> bullets;
    std::vector<Bullet> enemyBullets;
    float bulletSpeed;
    float noseOffset;

    // Nemici
    std::vector<Enemy> enemies;
    float enemySpeed;
    sf::Clock enemySpawnClock;
    sf::Time spawnRate;

    // Potenziamenti
    std::vector<PowerUp> powerUps;
    sf::Clock powerUpSpawnClock;
    sf::Time powerUpSpawnRate;
    bool hasSpread;
    sf::Clock spreadClock;
    bool hasShield;
    sf::CircleShape shieldVisual;
    bool isInvulnerable;
    sf::Clock invulnerabilityClock;

    // Effetti grafici
    std::vector<Particle> particles;
    float shakeDuration;
    float shakeIntensity;
    sf::View gameView;

    // Sistema Random
    std::mt19937 gen;
    std::uniform_int_distribution<> typeDist;
    std::uniform_int_distribution<> sideDist;
    std::uniform_real_distribution<float> xDist;
    std::uniform_real_distribution<float> yDist;

    // Sfondo stellato
    std::vector<Star> stars;
    std::uniform_real_distribution<float> xFullDist;
    std::uniform_real_distribution<float> yFullDist;
    std::uniform_real_distribution<float> radiusDist;
    std::uniform_int_distribution<> alphaDist;

    // Statistiche
    int score;
    int lives;
    sf::Clock dtClock;

    Game();
    void run();

    void resetGame();
    void spawnExplosion(sf::Vector2f pos, sf::Color color, int count = 15);
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
};