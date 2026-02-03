#include "Entity.h"

Entity::Entity() : velocity(0.f, 0.f), active(true), speed(0.f) {}

void Entity::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}

void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Entity::setPosition(const sf::Vector2f& pos) {
    sprite.setPosition(pos);
}

sf::FloatRect Entity::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Entity::isActive() const {
    return active;
}

void Entity::setActive(bool a) {
    active = a;
}

void Entity::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void Entity::setScale(float x, float y) {
    sprite.setScale(x, y);
}

sf::Sprite& Entity::getSprite() {
    return sprite;
}
