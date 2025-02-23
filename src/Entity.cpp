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

Entity::Entity(shared_ptr<Texture2D> texture, const Position &position) : Entity(texture)
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

void Entity::draw(const Position& cameraPosition)
{
    Position center(GetRenderWidth() / 2, GetRenderHeight() / 2);
    Position delta(m_position.x - cameraPosition.x, m_position.y - cameraPosition.y);

    DrawTexture(*m_texture, center.x + delta.x, center.y + delta.y, WHITE);
    DrawText(to_string(m_id).c_str(), center.x + delta.x, center.y + delta.y, 8, RED);
}

void Entity::kill()
{
    m_isAlive = false;
}

const Rectangle Entity::getHitbox()
{
    return getHitbox(m_position);
}

const Rectangle Entity::getHitbox(Position position)
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = m_texture->width;
    rect.height = m_texture->height;
    return rect;
}
