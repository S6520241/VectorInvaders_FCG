#include "Game.hpp"
#include "Config.hpp"
#include <iostream>
#include <cmath>

Game::Game() 
    : window(sf::VideoMode({Config::WindowWidth, Config::WindowHeight}), "VectorInvaders - Tappa04"),
      currentState(GameState::MainMenu),
      spawnRate(sf::seconds(1.0f)), // Genera un nemico ogni secondo
      gen(rd()),
      sideDist(0, 3), // 0: Alto, 1: Destra, 2: Basso, 3: Sinistra
      xDist(0.f, static_cast<float>(Config::WindowWidth)),
      yDist(0.f, static_cast<float>(Config::WindowHeight)),
      score(0),
      lives(3)
{
    window.setFramerateLimit(60);

    //Per centrare la finestra
    //________________________________________
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i centerPos(
        (desktop.size.x - window.getSize().x) / 2,
        (desktop.size.y - window.getSize().y) / 2
    );
    window.setPosition(centerPos);
    //______________________________________________________

    player.init();
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

        // Cambi di stato con la tastiera
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (currentState == GameState::MainMenu && keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                currentState = GameState::Gameplay;
                std::cout << "Sei nel GAMEPLAY. Usa WASD/Frecce per muoverti, Mouse per mirare, Tasto Sinistro per sparare. ESC per GameOver." << std::endl;
                // Resetta il timer di spawn appena si entra in gioco
                enemySpawnClock.restart();
            }
            else if (currentState == GameState::Gameplay && keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                currentState = GameState::GameOver;
                std::cout << "Sei nel GAME OVER. Premi INVIO per tornare al menu." << std::endl;
            }
            else if (currentState == GameState::GameOver && keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                currentState = GameState::MainMenu;
                std::cout << "Sei nel MAIN MENU. Premi INVIO per giocare." << std::endl;
                
                // Ripristino condizioni iniziali
                player.reset();
                bullets.clear();
                enemies.clear();
                score = 0;
                lives = 3;
            }
        }
        
        // Logica di sparo con il click del mouse
        if (currentState == GameState::Gameplay) {
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    shootBullet();
                }
            }
        }
    }
}

void Game::shootBullet() {
    Bullet newBullet;
    newBullet.shape.setSize({10.f, 4.f});
    newBullet.shape.setFillColor(sf::Color::Yellow);
    newBullet.shape.setOrigin({5.f, 2.f});

    float angleRad = player.shape.getRotation().asRadians();

    // Calcolo del punto di spawn
    sf::Vector2f spawnPos = player.shape.getPosition();
    spawnPos.x += std::cos(angleRad) * Config::NoseOffset;
    spawnPos.y += std::sin(angleRad) * Config::NoseOffset;
    
    newBullet.shape.setPosition(spawnPos);
    newBullet.shape.setRotation(player.shape.getRotation()); 

    // Calcolo della velocità costante in quella direzione
    newBullet.velocity.x = std::cos(angleRad) * Config::BulletSpeed;
    newBullet.velocity.y = std::sin(angleRad) * Config::BulletSpeed;

    bullets.push_back(newBullet);
}

void Game::updateBullets() {
    // Aggiornamento posizione proiettili e distruzione
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->shape.move(it->velocity);
        sf::Vector2f bPos = it->shape.getPosition();

        // Se il proiettile esce dallo schermo, cancellalo
        if (bPos.x < 0 || bPos.x > Config::WindowWidth || bPos.y < 0 || bPos.y > Config::WindowHeight) {
            it = bullets.erase(it); 
        } else {
            ++it; 
        }
    }
}

void Game::spawnEnemy() {
    // Generazione Nemici sui bordi esterni
    if (enemySpawnClock.getElapsedTime() >= spawnRate) {
        Enemy newEnemy;
        newEnemy.shape.setSize({30.f, 30.f});
        newEnemy.shape.setFillColor(sf::Color::Red);
        newEnemy.shape.setOrigin({15.f, 15.f});

        int side = sideDist(gen);
        float spawnX = 0.f;
        float spawnY = 0.f;

        // Spawna fuori dai bordi (800x600)
        if (side == 0) { spawnX = xDist(gen); spawnY = -50.f; } // Alto
        else if (side == 1) { spawnX = 850.f; spawnY = yDist(gen); } // Destra
        else if (side == 2) { spawnX = xDist(gen); spawnY = 650.f; } // Basso
        else { spawnX = -50.f; spawnY = yDist(gen); } // Sinistra

        newEnemy.shape.setPosition({spawnX, spawnY});
        enemies.push_back(newEnemy);
        enemySpawnClock.restart();
    }
}

void Game::updateEnemies() {
    // Aggiornamento posizione Nemici
    for (auto& enemy : enemies) {
        sf::Vector2f enemyPos = enemy.shape.getPosition();
        
        // Vettore di direzione
        float dx = player.shape.getPosition().x - enemyPos.x;
        float dy = player.shape.getPosition().y - enemyPos.y;
        
        // Calcolo della distanza
        float distance = std::sqrt(dx * dx + dy * dy);
        
        // Normalizzazione e movimento
        if (distance > 0.f) {
            float dirX = (dx / distance) * Config::EnemySpeed;
            float dirY = (dy / distance) * Config::EnemySpeed;
            enemy.shape.move({dirX, dirY});
        }
    }
}

void Game::handleCollisions() {
    // Proiettili contro Nemici
    for (auto bIt = bullets.begin(); bIt != bullets.end(); ) {
        bool bulletDestroyed = false;
        
        for (auto eIt = enemies.begin(); eIt != enemies.end(); ) {
            // Controlla l'intersezione tra le due hitbox
            if (bIt->shape.getGlobalBounds().findIntersection(eIt->shape.getGlobalBounds())) {
                eIt = enemies.erase(eIt); // Distruggi nemico
                score += 10;              // Incrementa il killScore
                bulletDestroyed = true;
                break;                    // Esci dal ciclo nemici per questo proiettile
            } else {
                ++eIt;
            }
        }
        
        if (bulletDestroyed) {
            bIt = bullets.erase(bIt);     // Distruggi proiettile
        } else {
            ++bIt;
        }
    }

    // Nemici contro Giocatore
    for (auto eIt = enemies.begin(); eIt != enemies.end(); ) {
        if (eIt->shape.getGlobalBounds().findIntersection(player.shape.getGlobalBounds())) {
            eIt = enemies.erase(eIt); // Rimuovi il nemico schiantato
            lives--;                  // Riduci la salute/vite
            
            std::cout << "Colpito! Vite rimanenti: " << lives << std::endl;
            
            if (lives <= 0) {
                currentState = GameState::GameOver;
                std::cout << "Sei nel GAME OVER. Punteggio finale: " << score << ". Premi INVIO per tornare al menu." << std::endl;
            }
        } else {
            ++eIt;
        }
    }
}

void Game::update() {
    if (currentState == GameState::Gameplay) {
        player.updateMovement(Config::PlayerSpeed);
        player.updateRotation(window);
        player.constrainBounds(static_cast<float>(Config::WindowWidth), static_cast<float>(Config::WindowHeight));
        
        updateBullets();
        spawnEnemy();
        updateEnemies();
        
        // --- MOTORE DI COLLISIONE ---
        handleCollisions();
    }
}

void Game::render() {
    switch (currentState) {
        case GameState::MainMenu:
            window.clear(sf::Color::Blue);
            break;
            
        case GameState::Gameplay:
            window.clear(sf::Color::Black);
            
            // Disegna prima i proiettili in modo che stiano "sotto" la navicella
            for (const auto& bullet : bullets) {
                window.draw(bullet.shape);
            }

            // Disegna i nemici
            for (const auto& enemy : enemies) {
                window.draw(enemy.shape);
            }
            
            // Disegna la navicella
            window.draw(player.shape); 
            break;
            
        case GameState::GameOver:
            window.clear(sf::Color::Red);
            break;
    }
    window.display();
}