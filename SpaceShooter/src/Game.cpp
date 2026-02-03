#include "Game.h"
#include "ResourceManager.h"
#include <sstream>
#include <iomanip>
#include <random>

Game::Game() 
    : window(sf::VideoMode(800, 600), "Space Shooter - Advanced Game Engine")
    , state(GameState::MENU)
    , score(0)
    , difficultyLevel(1.f)
    , enemySpawnTimer(0.f)
    , enemySpawnInterval(2.f)
    , menuSelection(0) {
    
    window.setFramerateLimit(60);
    
    // Load/create resources
    ResourceManager::getInstance().createProceduralTextures();
    
    // Setup fonts (using default font if file not available)
    sf::Font& font = ResourceManager::getInstance().loadFont("default", 
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    
    // Setup UI texts
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    
    healthText.setFont(font);
    healthText.setCharacterSize(20);
    healthText.setFillColor(sf::Color::Green);
    healthText.setPosition(10.f, 40.f);
    
    difficultyText.setFont(font);
    difficultyText.setCharacterSize(20);
    difficultyText.setFillColor(sf::Color::Yellow);
    difficultyText.setPosition(10.f, 70.f);
    
    // Menu texts
    menuTitle.setFont(font);
    menuTitle.setCharacterSize(60);
    menuTitle.setFillColor(sf::Color::Cyan);
    menuTitle.setString("SPACE SHOOTER");
    sf::FloatRect titleBounds = menuTitle.getLocalBounds();
    menuTitle.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    menuTitle.setPosition(400.f, 150.f);
    
    menuStart.setFont(font);
    menuStart.setCharacterSize(30);
    menuStart.setFillColor(sf::Color::White);
    menuStart.setString("> START GAME");
    sf::FloatRect startBounds = menuStart.getLocalBounds();
    menuStart.setOrigin(startBounds.width / 2.f, startBounds.height / 2.f);
    menuStart.setPosition(400.f, 300.f);
    
    menuExit.setFont(font);
    menuExit.setCharacterSize(30);
    menuExit.setFillColor(sf::Color::White);
    menuExit.setString("  EXIT");
    sf::FloatRect exitBounds = menuExit.getLocalBounds();
    menuExit.setOrigin(exitBounds.width / 2.f, exitBounds.height / 2.f);
    menuExit.setPosition(400.f, 360.f);
    
    // Game Over texts
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    sf::FloatRect govrBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(govrBounds.width / 2.f, govrBounds.height / 2.f);
    gameOverText.setPosition(400.f, 200.f);
    
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(30);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(300.f, 300.f);
    
    restartText.setFont(font);
    restartText.setCharacterSize(20);
    restartText.setFillColor(sf::Color::Yellow);
    restartText.setString("Press SPACE to return to menu");
    sf::FloatRect restartBounds = restartText.getLocalBounds();
    restartText.setOrigin(restartBounds.width / 2.f, restartBounds.height / 2.f);
    restartText.setPosition(400.f, 400.f);
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        // Cap delta time to prevent huge jumps
        if (dt > 0.1f) dt = 0.1f;
        
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        if (state == GameState::MENU) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    menuSelection = 0;
                }
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    menuSelection = 1;
                }
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                    if (menuSelection == 0) {
                        startGame();
                    } else {
                        window.close();
                    }
                }
            }
        }
        
        if (state == GameState::PLAYING) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (player && player->canShoot()) {
                    sf::Vector2f pos = player->getPosition();
                    bullets.push_back(std::make_unique<Bullet>(pos.x, pos.y - 20));
                    player->resetShootTimer();
                }
            }
        }
        
        if (state == GameState::GAME_OVER) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                state = GameState::MENU;
                resetGame();
            }
        }
    }
}

void Game::update(float dt) {
    switch (state) {
        case GameState::MENU:
            updateMenu();
            break;
        case GameState::PLAYING:
            updatePlaying(dt);
            break;
        case GameState::GAME_OVER:
            updateGameOver();
            break;
    }
}

void Game::updateMenu() {
    // Update menu selection indicator
    if (menuSelection == 0) {
        menuStart.setString("> START GAME");
        menuStart.setFillColor(sf::Color::Yellow);
        menuExit.setString("  EXIT");
        menuExit.setFillColor(sf::Color::White);
    } else {
        menuStart.setString("  START GAME");
        menuStart.setFillColor(sf::Color::White);
        menuExit.setString("> EXIT");
        menuExit.setFillColor(sf::Color::Yellow);
    }
    
    // Center texts
    sf::FloatRect startBounds = menuStart.getLocalBounds();
    menuStart.setOrigin(startBounds.width / 2.f, startBounds.height / 2.f);
    
    sf::FloatRect exitBounds = menuExit.getLocalBounds();
    menuExit.setOrigin(exitBounds.width / 2.f, exitBounds.height / 2.f);
}

void Game::updatePlaying(float dt) {
    // Update background
    background.update(dt);
    
    // Update player
    if (player) {
        player->update(dt);
        
        if (!player->isAlive()) {
            gameOver();
        }
    }
    
    // Update bullets
    for (auto& bullet : bullets) {
        bullet->update(dt);
    }
    
    // Update enemies
    for (auto& enemy : enemies) {
        enemy->update(dt);
    }
    
    // Update particles
    particleSystem.update(dt);
    
    // Spawn enemies
    enemySpawnTimer += dt;
    if (enemySpawnTimer >= enemySpawnInterval) {
        spawnEnemy();
        enemySpawnTimer = 0.f;
    }
    
    // Check collisions
    checkCollisions();
    
    // Cleanup inactive entities
    cleanupEntities();
    
    // Update difficulty based on score
    difficultyLevel = 1.f + (score / 100.f) * 0.5f;
    enemySpawnInterval = std::max(0.5f, 2.f / difficultyLevel);
    
    // Update UI
    std::stringstream ss;
    ss << "Score: " << score;
    scoreText.setString(ss.str());
    
    if (player) {
        ss.str("");
        ss << "Health: " << player->getHealth() << "/" << player->getMaxHealth();
        healthText.setString(ss.str());
    }
    
    ss.str("");
    ss << "Difficulty: " << std::fixed << std::setprecision(1) << difficultyLevel << "x";
    difficultyText.setString(ss.str());
}

void Game::updateGameOver() {
    std::stringstream ss;
    ss << "Final Score: " << score;
    finalScoreText.setString(ss.str());
    
    sf::FloatRect bounds = finalScoreText.getLocalBounds();
    finalScoreText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    finalScoreText.setPosition(400.f, 300.f);
}

void Game::render() {
    window.clear(sf::Color(10, 10, 30)); // Dark blue background
    
    switch (state) {
        case GameState::MENU:
            renderMenu();
            break;
        case GameState::PLAYING:
            renderPlaying();
            break;
        case GameState::GAME_OVER:
            renderGameOver();
            break;
    }
    
    window.display();
}

void Game::renderMenu() {
    window.draw(menuTitle);
    window.draw(menuStart);
    window.draw(menuExit);
}

void Game::renderPlaying() {
    // Render background
    background.render(window);
    
    // Render player
    if (player) {
        player->render(window);
    }
    
    // Render bullets
    for (auto& bullet : bullets) {
        bullet->render(window);
    }
    
    // Render enemies
    for (auto& enemy : enemies) {
        enemy->render(window);
    }
    
    // Render particles
    particleSystem.render(window);
    
    // Render UI
    window.draw(scoreText);
    window.draw(healthText);
    window.draw(difficultyText);
}

void Game::renderGameOver() {
    window.draw(gameOverText);
    window.draw(finalScoreText);
    window.draw(restartText);
}

void Game::spawnEnemy() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posX(50.f, 750.f);
    
    enemies.push_back(std::make_unique<Enemy>(posX(gen), -30.f, difficultyLevel));
}

void Game::checkCollisions() {
    if (!player) return;
    
    // Bullet vs Enemy collisions
    for (auto& bullet : bullets) {
        if (!bullet->isActive()) continue;
        
        for (auto& enemy : enemies) {
            if (!enemy->isActive()) continue;
            
            if (bullet->getBounds().intersects(enemy->getBounds())) {
                // Collision detected!
                bullet->setActive(false);
                enemy->setActive(false);
                
                // Increase score
                score += enemy->getScoreValue();
                
                // Create explosion effect
                sf::Vector2f pos = enemy->getPosition();
                particleSystem.createExplosion(pos.x, pos.y, 25);
            }
        }
    }
    
    // Enemy vs Player collisions
    for (auto& enemy : enemies) {
        if (!enemy->isActive()) continue;
        
        if (player->getBounds().intersects(enemy->getBounds())) {
            enemy->setActive(false);
            player->takeDamage(20);
            
            // Create explosion
            sf::Vector2f pos = enemy->getPosition();
            particleSystem.createExplosion(pos.x, pos.y, 15);
        }
    }
}

void Game::cleanupEntities() {
    // Remove inactive bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const std::unique_ptr<Bullet>& b) { return !b->isActive(); }),
        bullets.end()
    );
    
    // Remove inactive enemies
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& e) { return !e->isActive(); }),
        enemies.end()
    );
}

void Game::startGame() {
    state = GameState::PLAYING;
    
    // Create player
    player = std::make_unique<Player>();
    player->setPosition(400.f, 500.f);
    
    // Reset game stats
    score = 0;
    difficultyLevel = 1.f;
    enemySpawnTimer = 0.f;
    enemySpawnInterval = 2.f;
}

void Game::gameOver() {
    state = GameState::GAME_OVER;
}

void Game::resetGame() {
    // Clear all entities
    player.reset();
    bullets.clear();
    enemies.clear();
    particleSystem.clear();
    
    menuSelection = 0;
}
