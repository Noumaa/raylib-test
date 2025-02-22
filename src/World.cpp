#include "World.h"
#include "Player.h"
#include <algorithm>
#include <math.h>
#include "ResourceManager.h"
#include "Bullet.h"

World::World(int width, int height)
{
    m_width = width;
    m_height = height;
}

void World::update(const float &deltaTime)
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

    if (IsKeyPressed(KEY_SPACE))
    {
        Vector2 mousePos = GetMousePosition(); // Position de la souris
        Vector2 startPos = { static_cast<float>(player->getPosition().x), static_cast<float>(player->getPosition().y) };
    
        // Calcul de la direction normalisée
        Vector2 direction = { mousePos.x - startPos.x, mousePos.y - startPos.y };
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    
        if (length > 0) { 
            direction.x /= length;
            direction.y /= length;
        }
    
        float speed = 500.0f; // Vitesse de la balle
    
        addEntity(std::make_unique<Bullet>(ResourceManager::getInstance().getTexture("bullet.png"), player->getPosition(), direction, speed));
    }

    vector<Entity*> killedEntities;

    for (auto&& entity : m_entities)
    {
        if (!entity->isAlive())
        {
            killedEntities.push_back(entity.get());
            continue;
        }
        
        // TODO: Implement entities ID per world and Entity::getWorld
        switch (entity->getType())
        {
        case EntityType::Player:
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
            break;
        }
        case EntityType::Projectile:
        {
            Bullet* bullet = static_cast<Bullet*>(entity.get());

            // Reconstruire la liste des entitées sans le joueur
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
            break;
        }

        entity->update(deltaTime);
    }

    for (auto entity : killedEntities)
    {
        auto itr = std::find_if(std::begin(m_entities), 
            std::end(m_entities), 
            [entity](auto &element) { return element.get() == entity; });
        m_entities.erase(itr);
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
