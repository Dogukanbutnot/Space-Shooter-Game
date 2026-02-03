#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Particle.h"
#include "Background.h"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

class Game {
private:
    sf::RenderWindow window;
    GameState state;
    
    // Game objects
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bullet>> bullets;
    ParticleSystem particleSystem;
    Background background;
    
    // Game stats
    int score;
    float difficultyLevel;
    float enemySpawnTimer;
    float enemySpawnInterval;
    
    // UI elements
    sf::Text scoreText;
    sf::Text healthText;
    sf::Text difficultyText;
    sf::Text menuTitle;
    sf::Text menuStart;
    sf::Text menuExit;
    sf::Text gameOverText;
    sf::Text finalScoreText;
    sf::Text restartText;
    
    // Delta time
    sf::Clock clock;
    
    // Menu selection
    int menuSelection;
    
public:
    Game();
    
    void run();
    
private:
    void processEvents();
    void update(float dt);
    void render();
    
    void updateMenu();
    void updatePlaying(float dt);
    void updateGameOver();
    
    void renderMenu();
    void renderPlaying();
    void renderGameOver();
    
    void spawnEnemy();
    void checkCollisions();
    void cleanupEntities();
    
    void startGame();
    void gameOver();
    void resetGame();
};

#endif
