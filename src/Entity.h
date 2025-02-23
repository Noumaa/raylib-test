#pragma once
#include <raylib.h>
#include <memory>

using std::shared_ptr;

class World;

enum class EntityType {
    Player,
    Obstacle,
    Projectile,
};

class Entity
{
public:
    Entity(shared_ptr<Texture2D> texture);
    Entity(shared_ptr<Texture2D> texture, const Vector2& position);
    ~Entity() = default;

    virtual const EntityType    getType() { return EntityType::Obstacle; }

    virtual void                update(const float& deltaTime);
    virtual void                draw(const Vector2& cameraPosition);

    virtual void                kill();

    void                        setId(int id) { m_id = id; }
    const int&                  getId() { return m_id; }

    const bool&                 isAlive() { return m_isAlive; }

    void                        setWorld(World* world) { m_world = world; }
    World*                      getWorld() { return m_world; }

    const Vector2&              getPosition() { return m_position; }
    const Texture2D&            getTexture() { return *m_texture; }

    const Rectangle             getHitbox();
    const Rectangle             getHitbox(Vector2 position);
    
protected:
    int                         m_id;
    bool                        m_isAlive;

    World*                      m_world;
    Vector2                     m_position;

    shared_ptr<Texture2D>       m_texture;
};