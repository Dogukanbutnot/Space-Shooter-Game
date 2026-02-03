#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>

// Base class for all game objects (Player, Enemy, Bullet, etc.)
class Entity {
protected:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool active;
    float speed;

public:
    Entity();
    virtual ~Entity() = default;

    // Pure virtual functions - must be implemented by derived classes
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window);

    // Getters and setters
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);
    
    sf::FloatRect getBounds() const;
    bool isActive() const;
    void setActive(bool active);
    
    void setTexture(const sf::Texture& texture);
    void setScale(float x, float y);
    
    sf::Sprite& getSprite();
};

#endif
