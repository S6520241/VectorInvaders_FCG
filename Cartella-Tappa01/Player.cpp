#include "Player.hpp"
#include <SFML/Window.hpp>

Player::Player() {
    shape.setSize(sf::Vector2f({50.f, 20.f}));
    shape.setFillColor(sf::Color::Green);
    resetPosition();
}

void Player::resetPosition() {
    shape.setPosition({400.f, 300.f});
}

void Player::update() {
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
    
    // Sistema di collisione Navicella-Bordi espanso a tutti e 4 i lati
    sf::Vector2f pos = shape.getPosition();
    float hw = shape.getSize().x / 2.f;
    float hh = shape.getSize().y / 2.f;

    if (pos.x < hw) pos.x = hw;
    if (pos.x > 800.f - hw) pos.x = 800.f - hw;
    if (pos.y < hh) pos.y = hh;
    if (pos.y > 600.f - hh) pos.y = 600.f - hh;
    shape.setPosition(pos);
}