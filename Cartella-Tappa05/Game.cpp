#include "Game.hpp"
#include "Config.hpp"
#include <iostream>
#include <cmath>

Game::Game() 
    : window(sf::VideoMode({Config::WindowWidth, Config::WindowHeight}), "VectorInvaders - Tappa05"),
      currentState(GameState::MainMenu),
      player(playerTex), // <-- INIZIALIZZAZIONE RISOLTA
      spawnRate(sf::seconds(1.0f)), 
      gen(rd()),
      sideDist(0, 3), 
      xDist(0.f, static_cast<float>(Config::WindowWidth)),
      yDist(0.f, static_cast<float>(Config::WindowHeight)),
      score(0),
      lives(3)
{
    window.setFramerateLimit(60);

    //Per centrare la finestra
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i centerPos(
        (desktop.size.x - window.getSize().x) / 2,
        (desktop.size.y - window.getSize().y) / 2
    );
    window.setPosition(centerPos);

    loadResources();
    
    // Inizializza player con texture e coordinate centrali della finestra
    player.init(playerTex, Config::TargetPlayerSize, window.getSize().x / 2.f, window.getSize().y / 2.f);

    std::cout << "Sei nel MAIN MENU. Premi INVIO per giocare." << std::endl;
}

void Game::loadResources() {
    if (!playerTex.loadFromFile("../Cartella-risorse/player.png")) {
        std::cerr << "Errore: impossibile trovare player.png" << std::endl;
    }
    if (!enemyTex.loadFromFile("../Cartella-risorse/enemy.png")) {
        std::cerr << "Errore: impossibile trovare enemy.png" << std::endl;
    }
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
                std::cout << "Sei nel GAMEPLAY. Usa WASD/Frecce per muoverti, Mouse per mirare, Tasto Sinistro per sparare. ESC per GameOver." << std::endl;
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
                player.reset(400.f, 300.f);
                bullets.clear();
                enemies.clear();
                score = 0;
                lives = 3;
            }
        }
        
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

    float angleRad = player.shape.getRotation().asRadians() - 1.5707963f;

    sf::Vector2f spawnPos = player.shape.getPosition();
    spawnPos.x += std::cos(angleRad) * Config::NoseOffset;
    spawnPos.y += std::sin(angleRad) * Config::NoseOffset;
    
    newBullet.shape.setPosition(spawnPos);
    newBullet.shape.setRotation(player.shape.getRotation()); 

    newBullet.velocity.x = std::cos(angleRad) * Config::BulletSpeed;
    newBullet.velocity.y = std::sin(angleRad) * Config::BulletSpeed;

    bullets.push_back(newBullet);
}

void Game::updateBullets() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->shape.move(it->velocity);
        sf::Vector2f bPos = it->shape.getPosition();

        if (bPos.x < 0 || bPos.x > Config::WindowWidth || bPos.y < 0 || bPos.y > Config::WindowHeight) {
            it = bullets.erase(it); 
        } else {
            ++it; 
        }
    }
}

void Game::spawnEnemy() {
    if (enemySpawnClock.getElapsedTime() >= spawnRate) {
        Enemy newEnemy(enemyTex);
        newEnemy.shape.setOrigin({enemyTex.getSize().x / 2.f, enemyTex.getSize().y / 2.f});
        newEnemy.shape.setScale({0.5f, 0.5f});

        int side = sideDist(gen);
        float spawnX = 0.f;
        float spawnY = 0.f;

        if (side == 0) { spawnX = xDist(gen); spawnY = -50.f; } 
        else if (side == 1) { spawnX = 850.f; spawnY = yDist(gen); } 
        else if (side == 2) { spawnX = xDist(gen); spawnY = 650.f; } 
        else { spawnX = -50.f; spawnY = yDist(gen); } 

        float enemyScale = Config::TargetEnemySize / enemyTex.getSize().x;
        newEnemy.shape.setScale({enemyScale, enemyScale});
        
        newEnemy.shape.setPosition({spawnX, spawnY});
        enemies.push_back(newEnemy);
        enemySpawnClock.restart();
    }
}

void Game::updateEnemies() {
    for (auto& enemy : enemies) {
        sf::Vector2f enemyPos = enemy.shape.getPosition();
        float dx = player.shape.getPosition().x - enemyPos.x;
        float dy = player.shape.getPosition().y - enemyPos.y;
        
        float distance = std::sqrt(dx * dx + dy * dy);
        
        if (distance > 0.f) {
            float dirX = (dx / distance) * Config::EnemySpeed;
            float dirY = (dy / distance) * Config::EnemySpeed;
            enemy.shape.move({dirX, dirY});
        }
    }
}

void Game::handleCollisions() {
    for (auto bIt = bullets.begin(); bIt != bullets.end(); ) {
        bool bulletDestroyed = false;
        
        for (auto eIt = enemies.begin(); eIt != enemies.end(); ) {
            if (bIt->shape.getGlobalBounds().findIntersection(eIt->shape.getGlobalBounds())) {
                eIt = enemies.erase(eIt);
                score += 10;
                bulletDestroyed = true;
                break;
            } else {
                ++eIt;
            }
        }
        
        if (bulletDestroyed) {
            bIt = bullets.erase(bIt);
        } else {
            ++bIt;
        }
    }

    for (auto eIt = enemies.begin(); eIt != enemies.end(); ) {
        if (eIt->shape.getGlobalBounds().findIntersection(player.shape.getGlobalBounds())) {
            eIt = enemies.erase(eIt);
            lives--;
            
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
            for (const auto& bullet : bullets) {
                window.draw(bullet.shape);
            }
            for (const auto& enemy : enemies) {
                window.draw(enemy.shape);
            }
            window.draw(player.shape); 
            break;
            
        case GameState::GameOver:
            window.clear(sf::Color::Red);
            break;
    }
    window.display();
}