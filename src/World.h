#pragma once
#include "Entity.h"
#include <raylib.h>
#include <vector>

using std::vector, std::unique_ptr, std::move;

class World
{
public:
    World(int width, int height);
    ~World() = default;

    virtual void    update(const float& deltaTime);
    virtual void    draw();

    void            addEntity(unique_ptr<Entity> entity);
    void            removeEntity(int entityId);
    Entity*         getEntity(int entityId);

    int             getWidth() { return m_width; }
    int             getHeight() { return m_height; }

private:
    int             m_width;
    int             m_height;

    int             m_nextEntityId;
    int             m_playerId;
    vector<unique_ptr<Entity>> m_entities;
};
