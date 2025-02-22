#pragma once
#include <raylib.h>
#include <memory>

using std::shared_ptr;

struct Position
{
	int x;
	int y;

	Position() = default;
	Position(int _x, int _y)
        : x(_x), y(_y) {}

    bool operator ==(Position position) { return position.x == this->x && position.y == this->y; }
};

enum class EntityType {
    Player,
    Obstacle,
    Projectile,
};

class Entity
{
public:
    Entity(shared_ptr<Texture2D> texture);
    Entity(shared_ptr<Texture2D> texture, const Position& position);
    ~Entity() = default;

    virtual const EntityType    getType() { return EntityType::Obstacle; }

    virtual void                update(const float& deltaTime);
    virtual void                draw(const Position& cameraPosition);

    virtual void                kill();

    const bool&                 isAlive() { return m_isAlive; }

    const Position&             getPosition() { return m_position; }
    const Texture2D&            getTexture() { return *m_texture; }

    const Rectangle             getHitbox();
    const Rectangle             getHitbox(Position position);
    
protected:
    bool                        m_isAlive;

    Position                    m_position;
    shared_ptr<Texture2D>       m_texture;
};