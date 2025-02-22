#include "Entity.h"
#include <iostream>
#include "ResourceManager.h"

Entity::Entity(shared_ptr<Texture2D> texture)
{
    m_texture = texture;
}

Entity::Entity(shared_ptr<Texture2D> texture, const Position &position) : Entity(texture)
{
    m_position = position;
}

void Entity::update(const float &deltaTime)
{
}

void Entity::draw(const Position& cameraPosition)
{
    Position center(GetRenderWidth() / 2, GetRenderHeight() / 2);
    Position delta(m_position.x - cameraPosition.x, m_position.y - cameraPosition.y);

    DrawTexture(*m_texture, center.x + delta.x, center.y + delta.y, WHITE);
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
