#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    int health;
    int maxHealth;
    float shootCooldown;
    float shootTimer;

public:
    Player();
    
    void update(float dt) override;
    void handleInput(float dt);
    
    bool canShoot();
    void resetShootTimer();
    
    void takeDamage(int damage);
    int getHealth() const;
    int getMaxHealth() const;
    bool isAlive() const;
};

#endif
