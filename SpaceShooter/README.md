# 🚀 Space Shooter - Advanced 2D Game Engine

A professional-grade 2D Space Shooter game built with C++ and SFML, demonstrating advanced game development concepts and clean architecture.

## 🎯 Features

### 1. **Core Game Loop Architecture**
- **Input Processing**: Keyboard and event handling
- **Update Logic**: Frame-independent game logic using delta time
- **Rendering Pipeline**: Efficient sprite rendering system

### 2. **Entity Management System**
- **Inheritance-based Architecture**: Base `Entity` class for all game objects
- **Polymorphism**: Player, Enemy, Bullet all inherit from Entity
- **Vector-based Management**: Scalable object management using `std::vector`

### 3. **Delta Time Implementation**
- **Frame-independent Movement**: Speed calculated per second, not per frame
- **Consistent Gameplay**: Same speed on 60fps, 144fps, or any framerate
- **Professional Standard**: Industry-standard time management

### 4. **Resource Manager**
- **Singleton Pattern**: Single instance managing all resources
- **Memory Optimization**: Each texture loaded once, shared by all sprites
- **Procedural Generation**: Creates textures programmatically when files unavailable

### 5. **Collision Detection (AABB)**
- **Axis-Aligned Bounding Box**: Rectangle-based collision detection
- **Bullet vs Enemy**: Score increases on hit
- **Enemy vs Player**: Health damage on collision
- **Efficient Algorithm**: O(n*m) complexity with early exit optimization

### 6. **Particle System**
- **Explosion Effects**: 25 particles per enemy destruction
- **Physics Simulation**: Random velocities and directions
- **Fade-out Animation**: Alpha blending for smooth disappearance
- **Performance Optimized**: Automatic particle cleanup

### 7. **Scrolling Background (Parallax)**
- **Infinite Scrolling**: Seamless star field movement
- **Multiple Layers**: Different speeds create depth illusion
- **Dynamic Generation**: New stars spawn continuously
- **Performance Efficient**: Maximum 150 stars at once

### 8. **Difficulty Scaling System**
- **Progressive Challenge**: Difficulty increases with score
- **Speed Multiplier**: Enemies move faster at higher difficulties
- **Spawn Rate**: More frequent enemy waves
- **Formula**: `difficulty = 1 + (score / 100) * 0.5`

### 9. **HUD (Heads-Up Display)**
- **Real-time Stats**: Score, Health, Difficulty displayed
- **Professional UI**: Clean text rendering
- **Color-coded Information**: Green (health), Yellow (difficulty), White (score)

### 10. **Game State System**
- **MENU State**: Main menu with navigation
- **PLAYING State**: Active gameplay
- **GAME_OVER State**: End screen with final score
- **Clean Transitions**: State-based architecture

## 🎮 Controls

### Menu
- **↑/W**: Navigate up
- **↓/S**: Navigate down
- **Enter/Space**: Select option

### Gameplay
- **W/↑**: Move up
- **S/↓**: Move down
- **A/←**: Move left
- **D/→**: Move right
- **Space**: Shoot

### Game Over
- **Space**: Return to menu

## 📦 Installation

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install libsfml-dev g++ make

# Fedora
sudo dnf install SFML-devel gcc-c++ make

# Arch Linux
sudo pacman -S sfml gcc make

# macOS (with Homebrew)
brew install sfml
```

### Build Instructions
```bash
# Clone or extract the project
cd SpaceShooter

# Compile the game
make

# Run the game
./SpaceShooter

# Or compile and run in one command
make run
```

### Clean Build
```bash
make clean
make
```

## 🏗️ Project Structure
```
SpaceShooter/
├── include/              # Header files
│   ├── Entity.h         # Base class for all game objects
│   ├── Player.h         # Player character
│   ├── Enemy.h          # Enemy entities
│   ├── Bullet.h         # Projectiles
│   ├── Particle.h       # Particle system
│   ├── Background.h     # Scrolling background
│   ├── ResourceManager.h # Resource management
│   └── Game.h           # Main game class
├── src/                 # Implementation files
│   ├── Entity.cpp
│   ├── Player.cpp
│   ├── Enemy.cpp
│   ├── Bullet.cpp
│   ├── Particle.cpp
│   ├── Background.cpp
│   ├── ResourceManager.cpp
│   ├── Game.cpp
│   └── main.cpp         # Entry point
├── assets/              # Game assets (optional)
├── Makefile             # Build configuration
└── README.md            # This file
```

## 🔧 Technical Details

### Memory Management
- **Smart Pointers**: Uses `std::unique_ptr` for automatic memory management
- **RAII Pattern**: Resources automatically cleaned up
- **No Memory Leaks**: Proper object lifecycle management

### Performance Optimizations
- **Object Pooling**: Reuses inactive entities when possible
- **Batch Rendering**: Efficient sprite drawing
- **Lazy Evaluation**: Only updates active entities
- **Early Exit**: Collision detection stops after first hit

### Code Quality
- **Clean Code Principles**: Readable, maintainable code
- **SOLID Principles**: Single responsibility, Open/closed, etc.
- **Design Patterns**: Singleton, Factory, State pattern
- **Modern C++**: C++17 features, smart pointers, auto, lambdas

## 🎓 Learning Objectives

This project demonstrates:
1. ✅ **Game Loop Design**: Input → Update → Render cycle
2. ✅ **OOP Principles**: Inheritance, polymorphism, encapsulation
3. ✅ **Memory Management**: Smart pointers, resource management
4. ✅ **Physics Simulation**: Movement, collision detection
5. ✅ **Visual Effects**: Particles, animations, UI
6. ✅ **State Management**: Game state transitions
7. ✅ **Performance**: Delta time, optimization techniques
8. ✅ **Software Architecture**: Clean, scalable code structure

## 🚀 Future Enhancements

Potential features to add:
- [ ] Power-ups (shields, rapid fire, multi-shot)
- [ ] Multiple enemy types
- [ ] Boss fights
- [ ] Sound effects and music
- [ ] High score persistence
- [ ] Level system
- [ ] Multiple player ships
- [ ] Gamepad support
- [ ] Multiplayer mode

## 📝 Code Highlights

### Delta Time Example
```cpp
void Player::update(float dt) {
    sprite.move(velocity * dt);  // Speed independent of framerate!
}
```

### Resource Manager (Singleton)
```cpp
ResourceManager& rm = ResourceManager::getInstance();
sf::Texture& texture = rm.getTexture("player");  // Loaded once, used many times
```

### Collision Detection (AABB)
```cpp
if (bullet->getBounds().intersects(enemy->getBounds())) {
    // Collision detected!
}
```

### Particle System
```cpp
particleSystem.createExplosion(x, y, 25);  // 25 particles with physics!
```

## 🐛 Troubleshooting

### "SFML not found"
Make sure SFML is installed:
```bash
pkg-config --modversion sfml-all
```

### "Font not found" errors
The game will work with procedural graphics even without fonts. To add fonts:
```bash
# Verify font path in Game.cpp or use custom font
cp /path/to/your/font.ttf assets/
```

### Compilation errors
Ensure you're using C++17:
```bash
g++ --version  # Should be 7.0 or higher
```

## 📄 License
This project is for educational purposes. Feel free to learn from, modify, and extend it!

## 👨‍💻 Author
Created as a demonstration of professional game development techniques in C++.

---

**Happy Coding! 🎮**
