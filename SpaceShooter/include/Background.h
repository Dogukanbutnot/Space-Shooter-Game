#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>

class Star {
private:
    sf::Sprite sprite;
    float speed;

public:
    Star(float x, float y, float speed, const sf::Texture& texture);
    void update(float dt);
    void render(sf::RenderWindow& window);
};

class Background {
private:
    std::vector<Star> stars;
    float spawnTimer;
    float spawnInterval;

public:
    Background();
    
    void update(float dt);
    void render(sf::RenderWindow& window);
    void clear();
};

#endif
