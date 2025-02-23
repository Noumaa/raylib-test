#include "Player.h"
#include "World.h"
#include "ResourceManager.h"
#include "Bullet.h"
#include <iostream>
#include <math.h>

Player::Player(shared_ptr<Texture2D> texture, const Vector2 &position) : Entity(texture, position)
{
    m_world = nullptr;
}

void Player::update(const float &deltaTime, const vector<Entity *> &obstacles)
{
    Entity::update(deltaTime);

    Vector2 updatedPosition = m_position;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))   updatedPosition.x++;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))    updatedPosition.x--;

    if (updatedPosition.x != m_position.x)
    {
        for (Entity* obstacle : obstacles)
        {
            if (CheckCollisionRecs(getHitbox(updatedPosition), obstacle->getHitbox()))
            {
                // Cancel x-axis movement
                updatedPosition.x = m_position.x;
                break;
            }
        }
    }
    
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))      updatedPosition.y--;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))    updatedPosition.y++;

    if (updatedPosition.y != m_position.y)
    {
        for (Entity* obstacle : obstacles)
        {
            if (CheckCollisionRecs(getHitbox(updatedPosition), obstacle->getHitbox()))
            {
                // Cancel y-axis movement
                updatedPosition.y = m_position.y;
                break;
            }
        }
    }

    m_position = updatedPosition;
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouseScreenPos = GetMousePosition();

        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *m_camera);
        Vector2 startPos = { m_position.x, m_position.y };
    
        Vector2 direction = { mousePos.x - startPos.x, mousePos.y - startPos.y };
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    
        if (length > 0) { 
            direction.x /= length;
            direction.y /= length;
        }
    
        float speed = 1000;
    
        m_world->addEntity(std::make_unique<Bullet>(ResourceManager::getInstance().getTexture("bullet.png"), getPosition(), direction, speed));
    }
}
