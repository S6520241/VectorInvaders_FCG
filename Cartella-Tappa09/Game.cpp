#include "Game.hpp"
#include <iostream>
#include <cmath>

Game::Game() : 
    window(sf::VideoMode({800, 600}), "VectorInvaders - Tappa09"),
    currentState(GameState::MainMenu),
    survivalTime(0.0f),
    hudText(font),
    titleText(font),
    startText(font),  
    exitTextMenu(font), 
    promptText(font),        
    pauseText(font),         
    menuTextPause(font),     
    exitTextPause(font),     
    player(playerTex),       
    playerScale(1.0f),
    playerSpeed(5.0f),
    bulletSpeed(15.0f),
    noseOffset(25.0f),
    enemySpeed(2.0f),
    spawnRate(sf::seconds(1.0f)),
    powerUpSpawnRate(sf::seconds(10.0f)),
    hasSpread(false),
    hasShield(false),
    shieldVisual(40.f),
    isInvulnerable(false),
    shakeDuration(0.f),
    shakeIntensity(8.0f),
    typeDist(1, 100),
    sideDist(0, 3),
    xDist(50.f, 750.f),
    yDist(50.f, 550.f),
    xFullDist(0.f, 800.f),
    yFullDist(0.f, 600.f),
    radiusDist(0.5f, 2.5f),
    alphaDist(100, 255),
    score(0),
    lives(3)
{
    window.setFramerateLimit(60);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i centerPos(
        (desktop.size.x - window.getSize().x) / 2,
        (desktop.size.y - window.getSize().y) / 2
    );
    window.setPosition(centerPos);

    if (!playerTex.loadFromFile("../Cartella-risorse/player.png")) std::cerr << "Errore: player.png\n";
    if (!enemyTex.loadFromFile("../Cartella-risorse/enemy.png")) std::cerr << "Errore: enemy.png\n";
    if (!tankTex.loadFromFile("../Cartella-risorse/tank.png")) std::cerr << "Errore: tank.png\n";
    if (!shooterTex.loadFromFile("../Cartella-risorse/shooter.png")) std::cerr << "Errore: shooter.png\n";
    if (!spreadTex.loadFromFile("../Cartella-risorse/powerup_spread.png")) std::cerr << "Errore: powerup_spread.png\n";
    if (!shieldTex.loadFromFile("../Cartella-risorse/powerup_shield.png")) std::cerr << "Errore: powerup_shield.png\n";

    if (!font.openFromFile("../Cartella-risorse/font.ttf")) { std::cerr << "Errore: font.ttf\n";}

    hudText.setCharacterSize(20);
    hudText.setFillColor(sf::Color::White);
    hudText.setPosition({10.f, 10.f});

    titleText.setString("VECTOR INVADERS");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({titleBounds.size.x / 2.f, titleBounds.size.y / 2.f});
    titleText.setPosition({400.f, 150.f});

    startButton.setSize({200.f, 60.f});
    startButton.setFillColor(sf::Color(100, 100, 100));
    startButton.setOutlineThickness(2.f);
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOrigin({100.f, 30.f});
    startButton.setPosition({400.f, 300.f});

    startText.setString("INIZIA");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    sf::FloatRect startBounds = startText.getLocalBounds();
    startText.setOrigin({startBounds.size.x / 2.f, startBounds.size.y / 2.f});
    startText.setPosition(startButton.getPosition());

    exitButtonMenu.setSize({200.f, 60.f});
    exitButtonMenu.setFillColor(sf::Color(100, 100, 100));
    exitButtonMenu.setOutlineThickness(2.f);
    exitButtonMenu.setOutlineColor(sf::Color::White);
    exitButtonMenu.setOrigin({100.f, 30.f});
    exitButtonMenu.setPosition({400.f, 400.f});

    exitTextMenu.setString("ESCI");
    exitTextMenu.setCharacterSize(30);
    exitTextMenu.setFillColor(sf::Color::White);
    sf::FloatRect exitBoundsM = exitTextMenu.getLocalBounds();
    exitTextMenu.setOrigin({exitBoundsM.size.x / 2.f, exitBoundsM.size.y / 2.f});
    exitTextMenu.setPosition(exitButtonMenu.getPosition());

    promptText.setString("oppure premi INVIO per giocare");
    promptText.setCharacterSize(20);
    promptText.setFillColor(sf::Color(200, 200, 200));
    sf::FloatRect promptBounds = promptText.getLocalBounds();
    promptText.setOrigin({promptBounds.size.x / 2.f, promptBounds.size.y / 2.f});
    promptText.setPosition({400.f, 520.f});

    pauseOverlay.setSize({800.f, 600.f});
    pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));

    pauseText.setString("PAUSA");
    pauseText.setCharacterSize(40);
    pauseText.setFillColor(sf::Color::Yellow);
    sf::FloatRect pauseBounds = pauseText.getLocalBounds();
    pauseText.setOrigin({pauseBounds.size.x / 2.0f, pauseBounds.size.y / 2.0f});
    pauseText.setPosition({400.f, 150.f});

    menuButtonPause.setSize({350.f, 60.f});
    menuButtonPause.setFillColor(sf::Color(100, 100, 100));
    menuButtonPause.setOutlineThickness(2.f);
    menuButtonPause.setOutlineColor(sf::Color::White);
    menuButtonPause.setOrigin({175.f, 30.f});
    menuButtonPause.setPosition({400.f, 300.f});

    menuTextPause.setString("MENU PRINCIPALE");
    menuTextPause.setCharacterSize(25);
    menuTextPause.setFillColor(sf::Color::White);
    sf::FloatRect menuBoundsP = menuTextPause.getLocalBounds();
    menuTextPause.setOrigin({menuBoundsP.size.x / 2.f, menuBoundsP.size.y / 2.f});
    menuTextPause.setPosition(menuButtonPause.getPosition());

    exitButtonPause.setSize({350.f, 60.f});
    exitButtonPause.setFillColor(sf::Color(100, 100, 100));
    exitButtonPause.setOutlineThickness(2.f);
    exitButtonPause.setOutlineColor(sf::Color::White);
    exitButtonPause.setOrigin({175.f, 30.f});
    exitButtonPause.setPosition({400.f, 400.f});

    exitTextPause.setString("ESCI DAL GIOCO");
    exitTextPause.setCharacterSize(25);
    exitTextPause.setFillColor(sf::Color::White);
    sf::FloatRect exitBoundsP = exitTextPause.getLocalBounds();
    exitTextPause.setOrigin({exitBoundsP.size.x / 2.f, exitBoundsP.size.y / 2.f});
    exitTextPause.setPosition(exitButtonPause.getPosition());

    // Assegnazione Texture al Player post-caricamento
    player.setTexture(playerTex, true);
    playerScale = 50.f / playerTex.getSize().x;
    player.setScale({playerScale, playerScale});
    player.setOrigin({playerTex.getSize().x / 2.f, playerTex.getSize().y / 2.f});
    player.setPosition({400.f, 300.f});

    shieldVisual.setFillColor(sf::Color(0, 255, 255, 100));
    shieldVisual.setOrigin({40.f, 40.f});

    gameView = window.getDefaultView();

    std::random_device rd;
    gen.seed(rd());

    for (int i = 0; i < 150; ++i) {
        Star s;
        float r = radiusDist(gen);
        s.shape.setRadius(r);
        s.shape.setFillColor(sf::Color(255, 255, 255, alphaDist(gen)));
        s.shape.setPosition({xFullDist(gen), yFullDist(gen)});
        s.speed = r * 0.5f; 
        stars.push_back(s);
    }
}

void Game::run() {
    while (window.isOpen()) {
        sf::Time deltaTime = dtClock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::resetGame() {
    player.setPosition({400.f, 300.f});
    bullets.clear();
    enemyBullets.clear();
    enemies.clear();
    powerUps.clear();
    particles.clear();
    score = 0;
    lives = 3;
    survivalTime = 0.0f;
    hasSpread = false;
    hasShield = false;
    isInvulnerable = false;
    shakeDuration = 0.f;
    window.setView(window.getDefaultView());
}

void Game::spawnExplosion(sf::Vector2f pos, sf::Color color, int count) {
    std::uniform_real_distribution<float> angleDist(0.f, 6.28318f);
    std::uniform_real_distribution<float> speedDist(1.0f, 6.0f);
    std::uniform_real_distribution<float> lifeDist(0.2f, 0.6f);
    
    for (int i = 0; i < count; ++i) {
        Particle p;
        p.shape.setSize({4.f, 4.f});
        p.shape.setFillColor(color);
        p.shape.setOrigin({2.f, 2.f});
        p.shape.setPosition(pos);
        
        float angle = angleDist(gen);
        float speed = speedDist(gen);
        p.velocity = {std::cos(angle) * speed, std::sin(angle) * speed};
        p.lifetime = lifeDist(gen);
        p.maxLifetime = p.lifetime;
        particles.push_back(p);
    }
}

void Game::processEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (currentState == GameState::MainMenu && keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                currentState = GameState::Gameplay;
                enemySpawnClock.restart();
                powerUpSpawnClock.restart();
            }
            else if (currentState == GameState::Gameplay && keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                currentState = GameState::GameOver;
            }
            else if (currentState == GameState::GameOver && keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                resetGame();
                currentState = GameState::MainMenu;
            }
            else if (keyPressed->code == sf::Keyboard::Key::P) {
                if (currentState == GameState::Gameplay) {
                    currentState = GameState::Pause;
                } else if (currentState == GameState::Pause) {
                    currentState = GameState::Gameplay;
                }
            }
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (currentState == GameState::MainMenu) {
                    if (startButton.getGlobalBounds().contains(mousePos)) {
                        currentState = GameState::Gameplay;
                        enemySpawnClock.restart();
                        powerUpSpawnClock.restart();
                    }
                    if (exitButtonMenu.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }
                
                if (currentState == GameState::Pause) {
                    if (menuButtonPause.getGlobalBounds().contains(mousePos)) {
                        resetGame();
                        currentState = GameState::MainMenu;
                    }
                    if (exitButtonPause.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }

                if (currentState == GameState::Gameplay) {
                    float angleRad = player.getRotation().asRadians() - 1.5707963f;
                    sf::Vector2f spawnPos = player.getPosition();
                    spawnPos.x += std::cos(angleRad) * noseOffset;
                    spawnPos.y += std::sin(angleRad) * noseOffset;

                    auto spawnBullet = [&](float angleOffset) {
                        Bullet newBullet;
                        newBullet.shape.setSize({10.f, 4.f});
                        newBullet.shape.setFillColor(sf::Color::Yellow);
                        newBullet.shape.setOrigin({5.f, 2.f});
                        newBullet.shape.setPosition(spawnPos);
                        
                        float finalAngle = angleRad + angleOffset;
                        newBullet.shape.setRotation(sf::radians(finalAngle + 1.5707963f));
                        newBullet.velocity.x = std::cos(finalAngle) * bulletSpeed;
                        newBullet.velocity.y = std::sin(finalAngle) * bulletSpeed;
                        bullets.push_back(newBullet);
                    };

                    if (hasSpread) {
                        spawnBullet(-0.2f);
                        spawnBullet(0.0f);
                        spawnBullet(0.2f);
                    } else {
                        spawnBullet(0.0f);
                    }
                }
            }
        }
    }
}

void Game::update(sf::Time deltaTime) {
    sf::Vector2f mousePosHover = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    if (currentState == GameState::MainMenu) {
        if (startButton.getGlobalBounds().contains(mousePosHover)) startButton.setFillColor(sf::Color(150, 150, 150));
        else startButton.setFillColor(sf::Color(100, 100, 100));

        if (exitButtonMenu.getGlobalBounds().contains(mousePosHover)) exitButtonMenu.setFillColor(sf::Color(150, 150, 150));
        else exitButtonMenu.setFillColor(sf::Color(100, 100, 100));
    }
    else if (currentState == GameState::Pause) {
        if (menuButtonPause.getGlobalBounds().contains(mousePosHover)) menuButtonPause.setFillColor(sf::Color(150, 150, 150));
        else menuButtonPause.setFillColor(sf::Color(100, 100, 100));

        if (exitButtonPause.getGlobalBounds().contains(mousePosHover)) exitButtonPause.setFillColor(sf::Color(150, 150, 150));
        else exitButtonPause.setFillColor(sf::Color(100, 100, 100));
    }

    if (currentState == GameState::Gameplay) {
        for (auto& s : stars) {
            s.shape.move({0.f, s.speed});
            if (s.shape.getPosition().y > 600.f) {
                s.shape.setPosition({xFullDist(gen), -5.f});
            }
        }

        if (hasSpread && spreadClock.getElapsedTime().asSeconds() > 8.0f) hasSpread = false;
        if (isInvulnerable && invulnerabilityClock.getElapsedTime().asSeconds() > 1.5f) {
            isInvulnerable = false;
            player.setColor(sf::Color(255, 255, 255, 255));
        }

        if (isInvulnerable) {
            int alpha = (int)(std::sin(invulnerabilityClock.getElapsedTime().asMilliseconds() / 50.f) * 127 + 128);
            player.setColor(sf::Color(255, 255, 255, alpha));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.move({-playerSpeed, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.move({playerSpeed, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.move({0.f, -playerSpeed});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.move({0.f, playerSpeed});

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f playerPos = player.getPosition();
        player.setRotation(sf::radians(std::atan2(mousePos.y - playerPos.y, mousePos.x - playerPos.x) + 1.5707963f));

        sf::Vector2f pos = player.getPosition();
        float hw = player.getGlobalBounds().size.x / 2.f;
        float hh = player.getGlobalBounds().size.y / 2.f;
        if (pos.x < hw) pos.x = hw;
        if (pos.x > 800.f - hw) pos.x = 800.f - hw;
        if (pos.y < hh) pos.y = hh;
        if (pos.y > 600.f - hh) pos.y = 600.f - hh;
        player.setPosition(pos);

        if (hasShield) shieldVisual.setPosition(player.getPosition());

        for (auto pIt = particles.begin(); pIt != particles.end(); ) {
            pIt->lifetime -= 1.0f / 60.0f;
            if (pIt->lifetime <= 0) {
                pIt = particles.erase(pIt);
            } else {
                pIt->shape.move(pIt->velocity);
                sf::Color c = pIt->shape.getFillColor();
                c.a = static_cast<std::uint8_t>((pIt->lifetime / pIt->maxLifetime) * 255);
                pIt->shape.setFillColor(c);
                ++pIt;
            }
        }

        if (powerUpSpawnClock.getElapsedTime() >= powerUpSpawnRate) {
            PowerUpType pType = (typeDist(gen) > 50) ? PowerUpType::Spread : PowerUpType::Shield;
            const sf::Texture* pTex = (pType == PowerUpType::Spread) ? &spreadTex : &shieldTex;
            PowerUp pu(*pTex, pType);
            if (pTex->getSize().x > 0) {
                pu.shape.setOrigin({pTex->getSize().x / 2.f, pTex->getSize().y / 2.f});
                float scale = 30.f / pTex->getSize().x;
                pu.shape.setScale({scale, scale});
            }
            pu.shape.setPosition({xDist(gen), yDist(gen)});
            powerUps.push_back(pu);
            powerUpSpawnClock.restart();
        }

        for (auto pIt = powerUps.begin(); pIt != powerUps.end(); ) {
            if (pIt->shape.getGlobalBounds().findIntersection(player.getGlobalBounds())) {
                if (pIt->type == PowerUpType::Spread) { hasSpread = true; spreadClock.restart(); }
                else if (pIt->type == PowerUpType::Shield) { hasShield = true; }
                pIt = powerUps.erase(pIt);
            } else ++pIt;
        }

        for (auto it = bullets.begin(); it != bullets.end(); ) {
            it->shape.move(it->velocity);
            sf::Vector2f bPos = it->shape.getPosition();
            if (bPos.x < 0 || bPos.x > 800 || bPos.y < 0 || bPos.y > 600) it = bullets.erase(it);
            else ++it;
        }

        if (enemySpawnClock.getElapsedTime() >= spawnRate) {
            int roll = typeDist(gen);
            EnemyType spawnType;
            const sf::Texture* spawnTex;
            int spawnHp;
            if (roll <= 60) { spawnType = EnemyType::Base; spawnTex = &enemyTex; spawnHp = 1; }
            else if (roll <= 80) { spawnType = EnemyType::Tank; spawnTex = &tankTex; spawnHp = 3; }
            else { spawnType = EnemyType::Shooter; spawnTex = &shooterTex; spawnHp = 1; }
            
            Enemy newEnemy(*spawnTex, spawnType, spawnHp);
            float enemyScale = ((spawnType == EnemyType::Tank) ? 55.f : 30.f) / spawnTex->getSize().x;
            newEnemy.shape.setScale({enemyScale, enemyScale});
            newEnemy.shape.setOrigin({spawnTex->getSize().x / 2.f, spawnTex->getSize().y / 2.f});
            
            int side = sideDist(gen);
            float spawnX = 0.f, spawnY = 0.f;
            if (side == 0) { spawnX = (xDist(gen) - 50.f) * 1.2f; spawnY = -50.f; }
            else if (side == 1) { spawnX = 850.f; spawnY = (yDist(gen) - 50.f) * 1.2f; }
            else if (side == 2) { spawnX = (xDist(gen) - 50.f) * 1.2f; spawnY = 650.f; }
            else { spawnX = -50.f; spawnY = (yDist(gen) - 50.f) * 1.2f; }
            
            newEnemy.shape.setPosition({spawnX, spawnY});
            enemies.push_back(newEnemy);
            enemySpawnClock.restart();
        }

        for (auto& enemy : enemies) {
            sf::Vector2f enemyPos = enemy.shape.getPosition();
            float dx = player.getPosition().x - enemyPos.x;
            float dy = player.getPosition().y - enemyPos.y;
            float distance = std::sqrt(dx * dx + dy * dy);
            
            if (distance > 0.f) {
                float currentSpeed = (enemy.type == EnemyType::Tank) ? enemySpeed * 0.5f : enemySpeed;
                bool shouldMove = true;
                
                if (enemy.type == EnemyType::Shooter && distance < 250.f) {
                    shouldMove = false;
                    if (enemy.shootClock.getElapsedTime().asSeconds() >= 1.5f) {
                        Bullet eb;
                        eb.shape.setSize({8.f, 8.f});
                        eb.shape.setFillColor(sf::Color::Red);
                        eb.shape.setOrigin({4.f, 4.f});
                        eb.shape.setPosition(enemyPos);
                        eb.velocity.x = (dx / distance) * 7.0f;
                        eb.velocity.y = (dy / distance) * 7.0f;
                        enemyBullets.push_back(eb);
                        enemy.shootClock.restart();
                    }
                }
                if (shouldMove) enemy.shape.move({(dx / distance) * currentSpeed, (dy / distance) * currentSpeed});
            }
        }

        for (auto bIt = bullets.begin(); bIt != bullets.end(); ) {
            bool bulletDestroyed = false;
            for (auto eIt = enemies.begin(); eIt != enemies.end(); ) {
                if (bIt->shape.getGlobalBounds().findIntersection(eIt->shape.getGlobalBounds())) {
                    eIt->hp--;
                    spawnExplosion(eIt->shape.getPosition(), sf::Color(255, 200, 0), 5);
                    
                    if (eIt->hp <= 0) { 
                        spawnExplosion(eIt->shape.getPosition(), sf::Color::Red, 20);
                        eIt = enemies.erase(eIt); 
                        score += 10; 
                    }
                    else ++eIt;
                    
                    bulletDestroyed = true;
                    break;
                } else ++eIt;
            }
            if (bulletDestroyed) bIt = bullets.erase(bIt);
            else ++bIt;
        }

        auto takeDamage = [&]() {
            if (!isInvulnerable) {
                if (hasShield) {
                    hasShield = false;
                    isInvulnerable = true;
                    invulnerabilityClock.restart();
                    spawnExplosion(player.getPosition(), sf::Color::Cyan, 20);
                } else {
                    lives--;
                    isInvulnerable = true;
                    shakeDuration = 0.3f; 
                    invulnerabilityClock.restart();
                    spawnExplosion(player.getPosition(), sf::Color::Green, 30);
                    
                    if (lives <= 0) currentState = GameState::GameOver;
                }
            }
        };

        for (auto eIt = enemies.begin(); eIt != enemies.end(); ) {
            if (eIt->shape.getGlobalBounds().findIntersection(player.getGlobalBounds())) {
                eIt = enemies.erase(eIt);
                takeDamage();
            } else ++eIt;
        }

        for (auto ebIt = enemyBullets.begin(); ebIt != enemyBullets.end(); ) {
            ebIt->shape.move(ebIt->velocity);
            if (ebIt->shape.getGlobalBounds().findIntersection(player.getGlobalBounds())) {
                ebIt = enemyBullets.erase(ebIt);
                takeDamage();
            } 
            else if (ebIt->shape.getPosition().x < 0 || ebIt->shape.getPosition().x > 800 || 
                     ebIt->shape.getPosition().y < 0 || ebIt->shape.getPosition().y > 600) {
                ebIt = enemyBullets.erase(ebIt);
            } 
            else ++ebIt;
        }

        if (shakeDuration > 0.f) {
            shakeDuration -= 1.0f / 60.0f;
            std::uniform_real_distribution<float> shakeDist(-shakeIntensity, shakeIntensity);
            gameView.setCenter({400.f + shakeDist(gen), 300.f + shakeDist(gen)});
        } else {
            gameView.setCenter({400.f, 300.f});
        }
        window.setView(gameView);

        survivalTime += deltaTime.asSeconds();
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    if (currentState == GameState::MainMenu) {
        window.clear(sf::Color(20, 20, 50));
        window.draw(titleText);
        window.draw(startButton);
        window.draw(startText);
        window.draw(exitButtonMenu);
        window.draw(exitTextMenu);
        window.draw(promptText);
    } else if (currentState == GameState::GameOver) {
        window.clear(sf::Color::Red);
    } else if (currentState == GameState::Gameplay || currentState == GameState::Pause) {
        for (const auto& star : stars) window.draw(star.shape);
        for (const auto& pu : powerUps) window.draw(pu.shape);
        for (const auto& p : particles) window.draw(p.shape);
        for (const auto& bullet : bullets) window.draw(bullet.shape);
        for (const auto& eb : enemyBullets) window.draw(eb.shape);
        for (const auto& enemy : enemies) window.draw(enemy.shape);
        window.draw(player);
        if (hasShield) window.draw(shieldVisual);
        
        hudText.setString("Punteggio: " + std::to_string(score) + 
                  "\nVite: " + std::to_string(lives) + 
                  "\nTempo: " + std::to_string(static_cast<int>(survivalTime)) + "s");

        window.draw(hudText);

        if (currentState == GameState::Pause) {
            window.draw(pauseOverlay);
            window.draw(pauseText);
            window.draw(menuButtonPause);
            window.draw(menuTextPause);
            window.draw(exitButtonPause);
            window.draw(exitTextPause);
        }
    }
    
    window.display();
}