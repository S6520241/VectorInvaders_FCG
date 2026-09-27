// Game.cpp
#include "Game.hpp"
#include <iostream>

Game::Game() 
    : window(sf::VideoMode({800, 600}), "VectorInvaders - Tappa01"),
      currentState(GameState::MainMenu) 
{
    window.setFramerateLimit(60);
    std::cout << "Sei nel MAIN MENU. Premi INVIO per giocare." << std::endl;
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (currentState == GameState::MainMenu && keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                currentState = GameState::Gameplay;
                std::cout << "Sei nel GAMEPLAY. Usa le FRECCE DESTRA/SINISTRA per muoverti. Premi ESC per il Game Over." << std::endl;
            }
            else if (currentState == GameState::Gameplay && keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                currentState = GameState::GameOver;
                std::cout << "Sei nel GAME OVER. Premi INVIO per tornare al menu." << std::endl;
            }
            else if (currentState == GameState::GameOver && keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                currentState = GameState::MainMenu;
                std::cout << "Sei nel MAIN MENU. Premi INVIO per giocare." << std::endl;
                
                // Resettiamo la posizione del giocatore quando rinizia la partita
                player.resetPosition();
            }
        }
    }
}

void Game::update() {
    // INPUT IN TEMPO REALE E LOGICA DI GIOCO
    if (currentState == GameState::Gameplay) {
        player.update();
    }
}

void Game::render() {
    // RENDERING GRAFICO
    switch (currentState) {
        case GameState::MainMenu:
            window.clear(sf::Color::Blue);
            break;
            
        case GameState::Gameplay:
            window.clear(sf::Color::Black);
            window.draw(player.shape); 
            break;
            
        case GameState::GameOver:
            window.clear(sf::Color::Red);
            break;
    }

    window.display();
}