#include "Bullet.h"
#include "ResourceManager.h"

Bullet::Bullet(float x, float y) {
    speed = 500.f;
    setTexture(ResourceManager::getInstance().getTexture("bullet"));
    
    // Center the origin
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    
    setPosition(x, y);
    velocity.y = -speed;
}

void Bullet::update(float dt) {
    // Move upward
    sprite.move(velocity * dt);
    
    // Deactivate if off-screen
    if (sprite.getPosition().y < -20.f) {
        active = false;
    }
}
