#include "World.h"
#include "Player.h"
#include <algorithm>
#include <math.h>
#include <iostream>
#include "ResourceManager.h"
#include "Bullet.h"

using std::find_if;

World::World(int width, int height)
{
    m_width = width;
    m_height = height;

    m_nextEntityId = 0;
    m_playerId = -1;
}

void World::update(const float &deltaTime)
{
    Player* player = static_cast<Player*>(m_entities.at(m_playerId).get()); // Assuming the playerId is still referencing a Player entity

    vector<Entity*> killedEntities;

    for (auto&& entity : m_entities)
    {
        if (!entity->isAlive())
        {
            killedEntities.push_back(entity.get());
            continue;
        }
        
        switch (entity->getType())
        {
        case EntityType::Player:
        {
            vector<Entity*> obstacles;
            for (auto& obstacle : m_entities)
            {
                if (obstacle->getId() == m_playerId) continue;
                obstacles.push_back(obstacle.get());
            }

            player->update(deltaTime, obstacles);
            break;
        }
        case EntityType::Projectile:
        {
            Bullet* bullet = static_cast<Bullet*>(entity.get());

            vector<Entity*> obstacles;
            for (auto& obstacle : m_entities)
            {
                if (obstacle->getType() != EntityType::Obstacle) continue;
                obstacles.push_back(obstacle.get());
            }

            bullet->update(deltaTime, obstacles);
            break;
        }
        default:
            entity->update(deltaTime);
            break;
        }
    }

    for (auto entity : killedEntities)
    {
        removeEntity(entity->getId());
    }
}

void World::draw(Camera2D &camera)
{
    camera.target = getEntity(m_playerId)->getPosition();

    BeginMode2D(camera);

    // Drawing world's background
    DrawRectangle(0, 0, m_width, m_height, GREEN);

    for (auto&& entity : m_entities)
    {
        entity->draw(Vector2());
    }
    
    EndMode2D();
}

void World::addEntity(unique_ptr<Entity> entity)
{
    int nextEntityId = m_nextEntityId;

    if (entity->getType() == EntityType::Player)
    {
        if (m_playerId != -1)
        {
            std::cout << "This world already have a player, ID " << m_playerId << "\n";
            return;
        }
        m_playerId = nextEntityId; // Assuming the code below will works
    }

    entity->setId(nextEntityId);
    entity->setWorld(this);
    m_entities.push_back(std::move(entity));
    
    m_nextEntityId++;
}

void World::removeEntity(int entityId)
{
    auto it = find_if(m_entities.begin(), m_entities.end(), 
        [entityId](auto &entity) { return entity->getId() == entityId; });
    m_entities.erase(it);
}

// TODO: check valid id
Entity *World::getEntity(int entityId)
{
    auto it = find_if(m_entities.begin(), m_entities.end(), 
        [entityId](auto &entity) { return entity->getId() == entityId; });
    return it->get();
}
