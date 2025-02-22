#pragma once
#include "Entity.h"
#include <vector>

using std::vector;

class Player : public Entity
{
public:
    Player(shared_ptr<Texture2D> texture, const Position& position);
    ~Player() = default;

    virtual const EntityType getType() { return EntityType::Player; }

    virtual void update(const float& deltaTime, const vector<Entity*>& obstacles);

    const Position& getCameraPosition() { return m_position; }

private:
    Position m_cameraPosition;
};
