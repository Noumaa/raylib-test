#include "Bullet.h"
#include <iostream>

Bullet::Bullet(shared_ptr<Texture2D> texture, const Vector2& position, Vector2 direction, float speed) : Entity(texture, position)
{
    m_direction = direction;
    m_speed = speed;
}

void Bullet::update(const float& deltaTime, const vector<Entity*>& targets)
{
    Entity::update(deltaTime);

    m_position.x += m_direction.x * m_speed * deltaTime;
    m_position.y += m_direction.y * m_speed * deltaTime;

    for (Entity* entity : targets) {
        if (CheckCollisionRecs(getHitbox(), entity->getHitbox())) {
            kill();
            entity->kill();
            break;
        }
    }
}
