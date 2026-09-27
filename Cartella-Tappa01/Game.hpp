// Game.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameState.hpp"
#include "Player.hpp"

struct Game {
    sf::RenderWindow window;
    GameState currentState;
    Player player;

    Game();
    void run();
    
private:
    void processEvents();
    void update();
    void render();
};