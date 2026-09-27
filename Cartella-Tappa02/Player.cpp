#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>

void Player::init() {
    shape.setSize(sf::Vector2f({50.f, 20.f})); 
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin({25.f, 10.f});
    reset();
}

void Player::reset() {
    shape.setPosition({400.f, 300.f}); 
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
    shape.setRotation(sf::radians(std::atan2(dy, dx)));
}

void Player::constrainBounds(float windowWidth, float windowHeight) {
    sf::Vector2f pos = shape.getPosition();
    float hw = shape.getSize().x / 2.f;
    float hh = shape.getSize().y / 2.f;

    if (pos.x < hw) pos.x = hw;
    if (pos.x > windowWidth - hw) pos.x = windowWidth - hw;
    if (pos.y < hh) pos.y = hh;
    if (pos.y > windowHeight - hh) pos.y = windowHeight - hh;
    shape.setPosition(pos);
}