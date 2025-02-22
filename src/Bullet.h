#pragma once
#include "Entity.h"
#include <vector>

using std::vector;

class Bullet : public Entity
{
public:
    Bullet(shared_ptr<Texture2D> texture, const Position& position, Vector2 direction, float speed);
    ~Bullet() = default;

    virtual const EntityType getType() { return EntityType::Projectile; }

    virtual void update(const float& deltaTime, const vector<Entity*>& targets);
    
private:
    Vector2 m_direction;
    float m_speed;
};
