#include "Background.h"
#include "ResourceManager.h"
#include <random>

Star::Star(float x, float y, float spd, const sf::Texture& texture) : speed(spd) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    
    // Random brightness
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> brightness(100, 255);
    
    int bright = brightness(gen);
    sprite.setColor(sf::Color(bright, bright, bright));
}

void Star::update(float dt) {
    sprite.move(0.f, speed * dt);
    
    // Wrap around when off-screen
    if (sprite.getPosition().y > 620.f) {
        sprite.setPosition(sprite.getPosition().x, -20.f);
    }
}

void Star::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Background implementation
Background::Background() : spawnTimer(0.f), spawnInterval(0.1f) {
    const sf::Texture& texture = ResourceManager::getInstance().getTexture("star");
    
    // Create initial stars
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(0.f, 800.f);
    std::uniform_real_distribution<float> posY(0.f, 600.f);
    std::uniform_real_distribution<float> speed(20.f, 100.f);
    
    for (int i = 0; i < 100; ++i) {
        stars.emplace_back(posX(gen), posY(gen), speed(gen), texture);
    }
}

void Background::update(float dt) {
    for (auto& star : stars) {
        star.update(dt);
    }
    
    // Spawn new stars occasionally
    spawnTimer += dt;
    if (spawnTimer >= spawnInterval && stars.size() < 150) {
        const sf::Texture& texture = ResourceManager::getInstance().getTexture("star");
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> posX(0.f, 800.f);
        std::uniform_real_distribution<float> speed(20.f, 100.f);
        
        stars.emplace_back(posX(gen), -10.f, speed(gen), texture);
        spawnTimer = 0.f;
    }
}

void Background::render(sf::RenderWindow& window) {
    for (auto& star : stars) {
        star.render(window);
    }
}

void Background::clear() {
    stars.clear();
}
