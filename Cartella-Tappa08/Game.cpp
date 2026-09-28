#include "Game.hpp"
#include "Config.hpp"
#include <iostream>
#include <cmath>

Game::Game() 
    : window(sf::VideoMode({Config::WindowWidth, Config::WindowHeight}), "VectorInvaders - Tappa08"),
      currentState(GameState::MainMenu),
      player(playerTex),
      shakeDuration(0.f),
      spawnRate(sf::seconds(1.0f)),
      powerUpSpawnRate(sf::seconds(10.0f)),
      hasSpread(false),
      hasShield(false),
      shieldVisual(40.f),
      isInvulnerable(false),
      gen(rd()),
      typeDist(1, 100),
      sideDist(0, 3), 
      xDist(50.f, 750.f),
      yDist(50.f, 550.f),
      xFullDist(0.f, static_cast<float>(Config::WindowWidth)),
      yFullDist(0.f, static_cast<float>(Config::WindowHeight)),
      score(0),
      lives(3)
{
    window.setFramerateLimit(60);
    gameView = window.getDefaultView();

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i centerPos(
        (desktop.size.x - window.getSize().x) / 2,
        (desktop.size.y - window.getSize().y) / 2
    );
    window.setPosition(centerPos);

    shieldVisual.setFillColor(sf::Color(0, 255, 255, 100)); 
    shieldVisual.setOrigin({40.f, 40.f});

    loadResources();
    initStars();
    
    player.init(playerTex, Config::TargetPlayerSize, window.getSize().x / 2.f, window.getSize().y / 2.f);

    std::cout << "Sei nel MAIN MENU. Premi INVIO per giocare." << std::endl;
}

void Game::loadResources() {
    if (!playerTex.loadFromFile("../Cartella-risorse/player.png")) std::cerr << "Errore: player.png\n";
    if (!enemyTex.loadFromFile("../Cartella-risorse/enemy.png")) std::cerr << "Errore: enemy.png\n";
    if (!tankTex.loadFromFile("../Cartella-risorse/tank.png")) std::cerr << "Errore: tank.png\n";
    if (!shooterTex.loadFromFile("../Cartella-risorse/shooter.png")) std::cerr << "Errore: shooter.png\n";
    if (!spreadTex.loadFromFile("../Cartella-risorse/powerup_spread.png")) std::cerr << "Errore: powerup_spread.png\n";
    if (!shieldTex.loadFromFile("../Cartella-risorse/powerup_shield.png")) std::cerr << "Errore: powerup_shield.png\n";
}

void Game::initStars() {
    std::uniform_real_distribution<float> radiusDist(0.5f, 2.5f);
    std::uniform_int_distribution<> alphaDist(100, 255);

    for (int i = 0; i < Config::StarCount; ++i) {
        Star s;
        float r = radiusDist(gen);
        s.shape.setRadius(r);
        s.shape.setFillColor(sf::Color(255, 255, 255, alphaDist(gen)));
        s.shape.setPosition({xFullDist(gen), yFullDist(gen)});
        s.speed = r * 0.5f; 
        stars.push_back(s);
    }
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
                std::cout << "Sei nel GAMEPLAY. Usa WASD/Frecce, Mouse per mirare, Tasto Sinistro per sparare." << std::endl;
                enemySpawnClock.restart();
                powerUpSpawnClock.restart();
            }
            else if (currentState == GameState::Gameplay && keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                currentState = GameState::GameOver;
            }
            else if (currentState == GameState::GameOver && keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                currentState = GameState::MainMenu;
                
                player.reset(400.f, 300.f);
                bullets.clear();
                enemyBullets.clear();
                enemies.clear();
                powerUps.clear();
                particles.clear();
                score = 0;
                lives = 3;
                hasSpread = false;
                hasShield = false;
                isInvulnerable = false;
                shakeDuration = 0.f;
                window.setView(window.getDefaultView());
                player.shape.setColor(sf::Color(255, 255, 255, 255));
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
    float angleRad = player.shape.getRotation().asRadians() - 1.5707963f;
    sf::Vector2f spawnPos = player.shape.getPosition();
    spawnPos.x += std::cos(angleRad) * Config::NoseOffset;
    spawnPos.y += std::sin(angleRad) * Config::NoseOffset;

    auto spawnBullet = [&](float angleOffset) {
        Bullet newBullet;
        newBullet.shape.setSize({10.f, 4.f});
        newBullet.shape.setFillColor(sf::Color::Yellow);
        newBullet.shape.setOrigin({5.f, 2.f});
        newBullet.shape.setPosition(spawnPos);
        
        float finalAngle = angleRad + angleOffset;
        newBullet.shape.setRotation(sf::radians(finalAngle + 1.5707963f));
        newBullet.velocity.x = std::cos(finalAngle) * Config::BulletSpeed;
        newBullet.velocity.y = std::sin(finalAngle) * Config::BulletSpeed;
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

void Game::updateBullets() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->shape.move(it->velocity);
        sf::Vector2f bPos = it->shape.getPosition();
        if (bPos.x < 0 || bPos.x > Config::WindowWidth || bPos.y < 0 || bPos.y > Config::WindowHeight) {
            it = bullets.erase(it); 
        } else ++it; 
    }

    for (auto ebIt = enemyBullets.begin(); ebIt != enemyBullets.end(); ) {
        ebIt->shape.move(ebIt->velocity);
        sf::Vector2f bPos = ebIt->shape.getPosition();
        if (bPos.x < 0 || bPos.x > Config::WindowWidth || bPos.y < 0 || bPos.y > Config::WindowHeight) {
            ebIt = enemyBullets.erase(ebIt);
        } else ++ebIt;
    }
}

void Game::spawnEnemy() {
    if (enemySpawnClock.getElapsedTime() >= spawnRate) {
        int roll = typeDist(gen);
        EnemyType spawnType;
        const sf::Texture* spawnTex;
        int spawnHp;

        if (roll <= 60) { spawnType = EnemyType::Base; spawnTex = &enemyTex; spawnHp = 1; } 
        else if (roll <= 80) { spawnType = EnemyType::Tank; spawnTex = &tankTex; spawnHp = 3; } 
        else { spawnType = EnemyType::Shooter; spawnTex = &shooterTex; spawnHp = 1; }

        Enemy newEnemy(*spawnTex, spawnType, spawnHp);                
        float enemyScale = ((spawnType == EnemyType::Tank) ? Config::TargetTankSize : Config::TargetEnemySize) / spawnTex->getSize().x;
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
}

void Game::updateEnemies() {
    for (auto& enemy : enemies) {
        sf::Vector2f enemyPos = enemy.shape.getPosition();
        float dx = player.shape.getPosition().x - enemyPos.x;
        float dy = player.shape.getPosition().y - enemyPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        
        if (distance > 0.f) {
            float currentSpeed = (enemy.type == EnemyType::Tank) ? Config::EnemySpeed * 0.5f : Config::EnemySpeed;
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
}

void Game::spawnPowerUp() {
    if (powerUpSpawnClock.getElapsedTime() >= powerUpSpawnRate) {
        PowerUpType pType = (typeDist(gen) > 50) ? PowerUpType::Spread : PowerUpType::Shield;
        const sf::Texture* pTex = (pType == PowerUpType::Spread) ? &spreadTex : &shieldTex;
        
        PowerUp pu(*pTex, pType);
        if (pTex->getSize().x > 0) {
            pu.shape.setOrigin({pTex->getSize().x / 2.f, pTex->getSize().y / 2.f});
            float scale = Config::TargetPowerUpSize / pTex->getSize().x;
            pu.shape.setScale({scale, scale});
        }
        pu.shape.setPosition({xDist(gen), yDist(gen)});
        powerUps.push_back(pu);
        powerUpSpawnClock.restart();
    }
}

void Game::updatePowerUps() {
    for (auto pIt = powerUps.begin(); pIt != powerUps.end(); ) {
        if (pIt->shape.getGlobalBounds().findIntersection(player.shape.getGlobalBounds())) {
            if (pIt->type == PowerUpType::Spread) {
                hasSpread = true;
                spreadClock.restart();
            } else if (pIt->type == PowerUpType::Shield) {
                hasShield = true;
            }
            pIt = powerUps.erase(pIt);
        } else ++pIt;
    }
}

void Game::takeDamage() {
    if (!isInvulnerable) {
        if (hasShield) {
            hasShield = false;
            isInvulnerable = true;
            invulnerabilityClock.restart();
            spawnExplosion(player.shape.getPosition(), sf::Color::Cyan, 20);
        } else {
            lives--;
            isInvulnerable = true;
            shakeDuration = 0.3f;
            invulnerabilityClock.restart();
            spawnExplosion(player.shape.getPosition(), sf::Color::Green, 30);
            
            if (lives <= 0) currentState = GameState::GameOver;
        }
    }
}

void Game::handleCollisions() {
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
                } else ++eIt;
                
                bulletDestroyed = true;
                break;
            } else ++eIt;
        }
        if (bulletDestroyed) bIt = bullets.erase(bIt);
        else ++bIt;
    }

    for (auto eIt = enemies.begin(); eIt != enemies.end(); ) {
        if (eIt->shape.getGlobalBounds().findIntersection(player.shape.getGlobalBounds())) {
            eIt = enemies.erase(eIt);
            takeDamage();
        } else ++eIt;
    }

    for (auto ebIt = enemyBullets.begin(); ebIt != enemyBullets.end(); ) {
        if (ebIt->shape.getGlobalBounds().findIntersection(player.shape.getGlobalBounds())) {
            ebIt = enemyBullets.erase(ebIt);
            takeDamage();
        } else ++ebIt;
    }
}

void Game::updateVFX() {
    for (auto& s : stars) {
        s.shape.move({0.f, s.speed});
        if (s.shape.getPosition().y > Config::WindowHeight) {
            s.shape.setPosition({xFullDist(gen), -5.f});
        }
    }

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
}

void Game::applyScreenShake() {
    if (shakeDuration > 0.f) {
        shakeDuration -= 1.0f / 60.0f;
        std::uniform_real_distribution<float> shakeDist(-Config::ShakeIntensity, Config::ShakeIntensity);
        gameView.setCenter({Config::WindowWidth / 2.f + shakeDist(gen), Config::WindowHeight / 2.f + shakeDist(gen)});
    } else {
        gameView.setCenter({Config::WindowWidth / 2.f, Config::WindowHeight / 2.f});
    }
    window.setView(gameView);
}

void Game::update() {
    if (currentState == GameState::Gameplay) {
        updateVFX();
        
        if (hasSpread && spreadClock.getElapsedTime().asSeconds() > 8.0f) {
            hasSpread = false;
        }
        if (isInvulnerable && invulnerabilityClock.getElapsedTime().asSeconds() > 1.5f) {
            isInvulnerable = false;
            player.shape.setColor(sf::Color(255, 255, 255, 255));
        }
        if (isInvulnerable) {
            int alpha = (int)(std::sin(invulnerabilityClock.getElapsedTime().asMilliseconds() / 50.f) * 127 + 128);
            player.shape.setColor(sf::Color(255, 255, 255, alpha));
        }

        player.updateMovement(Config::PlayerSpeed);
        player.updateRotation(window);
        player.constrainBounds(static_cast<float>(Config::WindowWidth), static_cast<float>(Config::WindowHeight));
        
        if (hasShield) {
            shieldVisual.setPosition(player.shape.getPosition());
        }

        updateBullets();
        spawnPowerUp();
        updatePowerUps();
        spawnEnemy();
        updateEnemies();
        handleCollisions();
        
        applyScreenShake();
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    if (currentState == GameState::MainMenu) {
        window.clear(sf::Color::Blue);
    } else if (currentState == GameState::GameOver) {
        window.clear(sf::Color::Red);
    } else if (currentState == GameState::Gameplay) {
        for (const auto& star : stars) window.draw(star.shape);
        for (const auto& pu : powerUps) window.draw(pu.shape);
        for (const auto& p : particles) window.draw(p.shape);
        for (const auto& bullet : bullets) window.draw(bullet.shape);
        for (const auto& eb : enemyBullets) window.draw(eb.shape);
        for (const auto& enemy : enemies) window.draw(enemy.shape);
        window.draw(player.shape); 
        if (hasShield) window.draw(shieldVisual);
    }
    
    window.display();
}