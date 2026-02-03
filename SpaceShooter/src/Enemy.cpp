#include "Enemy.h"
#include "ResourceManager.h"

Enemy::Enemy(float x, float y, float speedMultiplier) : scoreValue(10) {
    speed = 100.f * speedMultiplier;
    setTexture(ResourceManager::getInstance().getTexture("enemy"));
    
    // Center the origin
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    
    setPosition(x, y);
    velocity.y = speed;
}

void Enemy::update(float dt) {
    // Move downward
    sprite.move(velocity * dt);
    
    // Deactivate if off-screen
    if (sprite.getPosition().y > 650.f) {
        active = false;
    }
}

int Enemy::getScoreValue() const {
    return scoreValue;
}
