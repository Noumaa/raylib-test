#include "Player.h"
#include "World.h"
#include "ResourceManager.h"
#include "Bullet.h"
#include <iostream>
#include <math.h>

Player::Player(shared_ptr<Texture2D> texture, const Position &position) : Entity(texture, position)
{
    m_world = nullptr;
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
    

    if (IsKeyPressed(KEY_SPACE))
    {
        Vector2 mousePos = GetMousePosition(); // Position de la souris
        Vector2 startPos = { static_cast<float>(getPosition().x), static_cast<float>(getPosition().y) };
    
        // Calcul de la direction normalisée
        Vector2 direction = { mousePos.x - startPos.x, mousePos.y - startPos.y };
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    
        if (length > 0) { 
            direction.x /= length;
            direction.y /= length;
        }
    
        float speed = 500.0f; // Vitesse de la balle
    
        m_world->addEntity(std::make_unique<Bullet>(ResourceManager::getInstance().getTexture("bullet.png"), getPosition(), direction, speed));
    }
}
