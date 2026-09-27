#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "GameState.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

struct Game {
    sf::RenderWindow window;
    GameState currentState;
    
    // Variabili del giocatore e proiettili
    Player player;
    std::vector<Bullet> bullets;

    Game();
    void run();

    void processEvents();
    void update();
    void render();
    void shootBullet();
};