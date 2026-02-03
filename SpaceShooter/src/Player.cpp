#include "Player.h"
#include "ResourceManager.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player() : health(100), maxHealth(100), shootCooldown(0.2f), shootTimer(0.f) {
    speed = 300.f;
    setTexture(ResourceManager::getInstance().getTexture("player"));
    
    // Center the origin
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::update(float dt) {
    handleInput(dt);
    
    // Update shoot timer
    if (shootTimer > 0.f) {
        shootTimer -= dt;
    }
    
    // Apply velocity (with delta time for frame-independent movement)
    sprite.move(velocity * dt);
    
    // Keep player within screen bounds
    sf::Vector2f pos = sprite.getPosition();
    if (pos.x < 20.f) pos.x = 20.f;
    if (pos.x > 780.f) pos.x = 780.f;
    if (pos.y < 20.f) pos.y = 20.f;
    if (pos.y > 580.f) pos.y = 580.f;
    sprite.setPosition(pos);
}

void Player::handleInput(float dt) {
    velocity = sf::Vector2f(0.f, 0.f);
    
    // Movement with WASD or Arrow keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocity.y = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = speed;
    }
    
    // Normalize diagonal movement
    if (velocity.x != 0.f && velocity.y != 0.f) {
        float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity.x = (velocity.x / length) * speed;
        velocity.y = (velocity.y / length) * speed;
    }
}

bool Player::canShoot() {
    return shootTimer <= 0.f;
}

void Player::resetShootTimer() {
    shootTimer = shootCooldown;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

int Player::getHealth() const {
    return health;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

bool Player::isAlive() const {
    return health > 0;
}
