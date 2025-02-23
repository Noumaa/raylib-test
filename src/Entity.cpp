#include "Entity.h"
#include "ResourceManager.h"
#include "World.h"
#include <iostream>

using std::to_string;

Entity::Entity(shared_ptr<Texture2D> texture)
{
    m_id = -1;
    m_isAlive = true;
    
    m_texture = texture;
}

Entity::Entity(shared_ptr<Texture2D> texture, const Vector2 &position) : Entity(texture)
{
    m_position = position;
}

void Entity::update(const float &deltaTime)
{
    Rectangle world;
    world.width = getWorld()->getWidth();
    world.height = getWorld()->getHeight();
    if (!CheckCollisionRecs(world, getHitbox()))
    {
        m_isAlive = false;
    }
}

void Entity::draw(const Vector2& cameraPosition)
{
    DrawTexture(*m_texture, m_position.x, m_position.y, WHITE);
    DrawText(to_string(m_id).c_str(), m_position.x, m_position.y, 8, RED);
}

void Entity::kill()
{
    m_isAlive = false;
}

const Rectangle Entity::getHitbox()
{
    return getHitbox(m_position);
}

const Rectangle Entity::getHitbox(Vector2 position)
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = m_texture->width;
    rect.height = m_texture->height;
    return rect;
}
