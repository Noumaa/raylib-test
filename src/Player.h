#pragma once
#include "Entity.h"
#include <vector>

using std::vector;

class Player : public Entity
{
public:
    Player(shared_ptr<Texture2D> texture, const Vector2& position);
    ~Player() = default;

    virtual const EntityType    getType() { return EntityType::Player; }

    virtual void                update(const float& deltaTime, const vector<Entity*>& obstacles);

    void                        setCamera(const Camera2D* camera) { m_camera = camera; }

private:
    const Camera2D*             m_camera;
};
