#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(float x, float y);
    
    void update(float dt) override;
};

#endif
