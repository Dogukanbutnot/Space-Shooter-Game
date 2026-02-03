#include "Particle.h"
#include "ResourceManager.h"
#include <cmath>
#include <random>

Particle::Particle(float x, float y, const sf::Texture& texture) 
    : lifetime(0.f), maxLifetime(1.f), active(true) {
    
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    
    // Random velocity
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angle(0.f, 6.28318f); // 0 to 2*PI
    std::uniform_real_distribution<float> speed(50.f, 200.f);
    
    float ang = angle(gen);
    float spd = speed(gen);
    velocity.x = std::cos(ang) * spd;
    velocity.y = std::sin(ang) * spd;
    
    // Random lifetime
    std::uniform_real_distribution<float> life(0.5f, 1.5f);
    maxLifetime = life(gen);
}

void Particle::update(float dt) {
    if (!active) return;
    
    lifetime += dt;
    if (lifetime >= maxLifetime) {
        active = false;
        return;
    }
    
    // Move particle
    sprite.move(velocity * dt);
    
    // Fade out over time
    float alpha = 1.f - (lifetime / maxLifetime);
    sf::Color color = sprite.getColor();
    color.a = static_cast<sf::Uint8>(alpha * 255);
    sprite.setColor(color);
}

void Particle::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

bool Particle::isActive() const {
    return active;
}

// ParticleSystem implementation
void ParticleSystem::createExplosion(float x, float y, int particleCount) {
    const sf::Texture& texture = ResourceManager::getInstance().getTexture("particle");
    
    for (int i = 0; i < particleCount; ++i) {
        particles.emplace_back(x, y, texture);
    }
}

void ParticleSystem::update(float dt) {
    for (auto& particle : particles) {
        particle.update(dt);
    }
    
    // Remove dead particles
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return !p.isActive(); }),
        particles.end()
    );
}

void ParticleSystem::render(sf::RenderWindow& window) {
    for (auto& particle : particles) {
        particle.render(window);
    }
}

void ParticleSystem::clear() {
    particles.clear();
}
