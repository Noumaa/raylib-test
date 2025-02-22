#pragma once
#include <memory>
#include <unordered_map>
#include <raylib.h>

using std::shared_ptr, std::weak_ptr, std::unordered_map;

class ResourceManager
{
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    static ResourceManager& getInstance();

    shared_ptr<Texture2D>   getTexture(const char* fileName);

private:
    unordered_map<const char*, weak_ptr<Texture2D>> m_textures;
};
