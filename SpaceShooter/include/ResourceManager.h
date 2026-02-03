#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

// Singleton pattern for managing game resources
class ResourceManager {
private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;
    
    ResourceManager() = default;

public:
    // Singleton instance
    static ResourceManager& getInstance();
    
    // Delete copy constructor and assignment operator
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    // Load and get texture
    sf::Texture& loadTexture(const std::string& name, const std::string& filename);
    sf::Texture& getTexture(const std::string& name);
    
    // Load and get font
    sf::Font& loadFont(const std::string& name, const std::string& filename);
    sf::Font& getFont(const std::string& name);
    
    // Create procedural textures (for when we don't have image files)
    void createProceduralTextures();
};

#endif
