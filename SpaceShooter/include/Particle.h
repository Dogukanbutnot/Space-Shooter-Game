#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float lifetime;
    float maxLifetime;
    bool active;

public:
    Particle(float x, float y, const sf::Texture& texture);
    
    void update(float dt);
    void render(sf::RenderWindow& window);
    
    bool isActive() const;
};

class ParticleSystem {
private:
    std::vector<Particle> particles;

public:
    void createExplosion(float x, float y, int particleCount = 20);
    void update(float dt);
    void render(sf::RenderWindow& window);
    void clear();
};

#endif
