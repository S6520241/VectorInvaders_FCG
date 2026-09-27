#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>

Player::Player(const sf::Texture& texture) : shape(texture) {
}

void Player::init(const sf::Texture& texture, float targetSize, float startX, float startY) {
    // AGGIUNTO 'true': forza lo sprite ad aggiornare le sue dimensioni (TextureRect)
    // sulla base della texture che ora è effettivamente caricata.
    shape.setTexture(texture, true);
    
    float scale = targetSize / texture.getSize().x;
    
    // Mantiene le proporzioni originali dell'immagine
    shape.setScale({scale, scale});
    
    // Imposta il centro usando la grandezza reale della texture
    shape.setOrigin({texture.getSize().x / 2.f, texture.getSize().y / 2.f});
    reset(startX, startY);
}

void Player::reset(float startX, float startY) {
    shape.setPosition({startX, startY});
}

void Player::updateMovement(float speed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        shape.move({-speed, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        shape.move({speed, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        shape.move({0.f, -speed});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        shape.move({0.f, speed});
    }
}

void Player::updateRotation(const sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f playerPos = shape.getPosition();
    float dy = mousePos.y - playerPos.y;
    float dx = mousePos.x - playerPos.x;
    shape.setRotation(sf::radians(std::atan2(dy, dx) + 1.5707963f));
}

void Player::constrainBounds(float windowWidth, float windowHeight) {
    sf::Vector2f pos = shape.getPosition();
    float hw = shape.getGlobalBounds().size.x / 2.f;
    float hh = shape.getGlobalBounds().size.y / 2.f;

    if (pos.x < hw) pos.x = hw;
    if (pos.x > windowWidth - hw) pos.x = windowWidth - hw;
    if (pos.y < hh) pos.y = hh;
    if (pos.y > windowHeight - hh) pos.y = windowHeight - hh;
    shape.setPosition(pos);
}