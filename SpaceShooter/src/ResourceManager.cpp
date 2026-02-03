#include "ResourceManager.h"
#include <iostream>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

sf::Texture& ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return *it->second;
    }
    
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }
    
    textures[name] = std::move(texture);
    return *textures[name];
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it == textures.end()) {
        std::cerr << "Texture not found: " << name << std::endl;
        static sf::Texture dummy;
        return dummy;
    }
    return *it->second;
}

sf::Font& ResourceManager::loadFont(const std::string& name, const std::string& filename) {
    auto it = fonts.find(name);
    if (it != fonts.end()) {
        return *it->second;
    }
    
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filename)) {
        std::cerr << "Failed to load font: " << filename << std::endl;
    }
    
    fonts[name] = std::move(font);
    return *fonts[name];
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    auto it = fonts.find(name);
    if (it == fonts.end()) {
        std::cerr << "Font not found: " << name << std::endl;
        static sf::Font dummy;
        return dummy;
    }
    return *it->second;
}

void ResourceManager::createProceduralTextures() {
    // Create player texture (green triangle)
    {
        sf::Image img;
        img.create(32, 32, sf::Color::Transparent);
        for (int y = 0; y < 32; ++y) {
            for (int x = 0; x < 32; ++x) {
                // Draw a triangle shape
                if (y > 4 && abs(x - 16) < (32 - y) / 2) {
                    img.setPixel(x, y, sf::Color::Green);
                }
            }
        }
        auto texture = std::make_unique<sf::Texture>();
        texture->loadFromImage(img);
        textures["player"] = std::move(texture);
    }
    
    // Create enemy texture (red inverted triangle)
    {
        sf::Image img;
        img.create(32, 32, sf::Color::Transparent);
        for (int y = 0; y < 32; ++y) {
            for (int x = 0; x < 32; ++x) {
                if (y < 28 && abs(x - 16) < y / 2) {
                    img.setPixel(x, y, sf::Color::Red);
                }
            }
        }
        auto texture = std::make_unique<sf::Texture>();
        texture->loadFromImage(img);
        textures["enemy"] = std::move(texture);
    }
    
    // Create bullet texture (yellow rectangle)
    {
        sf::Image img;
        img.create(8, 16, sf::Color::Yellow);
        auto texture = std::make_unique<sf::Texture>();
        texture->loadFromImage(img);
        textures["bullet"] = std::move(texture);
    }
    
    // Create particle texture (white square)
    {
        sf::Image img;
        img.create(4, 4, sf::Color::White);
        auto texture = std::make_unique<sf::Texture>();
        texture->loadFromImage(img);
        textures["particle"] = std::move(texture);
    }
    
    // Create background star texture
    {
        sf::Image img;
        img.create(2, 2, sf::Color::White);
        auto texture = std::make_unique<sf::Texture>();
        texture->loadFromImage(img);
        textures["star"] = std::move(texture);
    }
}
