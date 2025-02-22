#include "World.h"
#include "Player.h"
#include <algorithm>

World::World(int width, int height)
{
    m_width = width;
    m_height = height;
}

void World::update(const float &deltaTime)
{
    for (auto&& entity : m_entities)
    {
        if (entity->getType() == EntityType::Player) // TODO: Implement entities ID per world
        {
            Player* player = static_cast<Player*>(entity.get());

            // Reconstruire la liste des entitées sans le joueur
            vector<Entity*> obstacles;
            for (auto& obstacle : m_entities)
            {
                if (obstacle->getType() == EntityType::Player) continue;
                obstacles.push_back(obstacle.get());
            }

            player->update(deltaTime, obstacles);
            continue;
        }
        entity->update(deltaTime);
    }
}

void World::draw()
{
    Player* player;
    for (auto&& entity : m_entities)
    {
        if (entity->getType() == EntityType::Player)
        {
            player = static_cast<Player*>(entity.get());
            break;
        }
    }

    const Position& cameraPosition = player->getCameraPosition();

    Position center(GetRenderWidth() / 2, GetRenderHeight() / 2);
    Position delta(-cameraPosition.x, -cameraPosition.y);

    DrawRectangle(center.x + delta.x, center.y + delta.y, m_width, m_height, GREEN);

    for (auto&& entity : m_entities)
    {
        entity->draw(cameraPosition);
    }
}

void World::addEntity(unique_ptr<Entity> entity)
{
    m_entities.push_back(std::move(entity));
}
