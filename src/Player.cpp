#include "Player.h"
#include <iostream>

Player::Player(shared_ptr<Texture2D> texture, const Position &position) : Entity(texture, position)
{
}

void Player::update(const float &deltaTime, const vector<Entity *> &obstacles)
{
    Entity::update(deltaTime);

    Position updatedPosition = m_position;
    if (IsKeyDown(KEY_RIGHT))   updatedPosition.x++;
    if (IsKeyDown(KEY_LEFT))    updatedPosition.x--;

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
    
    if (IsKeyDown(KEY_UP))      updatedPosition.y--;
    if (IsKeyDown(KEY_DOWN))    updatedPosition.y++;

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
}
