#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
private:
    int scoreValue;

public:
    Enemy(float x, float y, float speedMultiplier = 1.f);
    
    void update(float dt) override;
    int getScoreValue() const;
};

#endif
