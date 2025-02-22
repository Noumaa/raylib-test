#include "ResourceManager.h"

ResourceManager &ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

shared_ptr<Texture2D> ResourceManager::getTexture(const char *fileName)
{
    // Search the texture
    auto it = m_textures.find(fileName);
    if (it != m_textures.end())
    {
        // Returning the pointer if valid
        if (auto sharedTexture = it->second.lock())
            return sharedTexture;
    }

    // Otherwise load the texture, defining its desctructor and adding it to the map
    Texture2D texture = LoadTexture(fileName);
    auto sharedTexture = shared_ptr<Texture2D>(new Texture2D(texture), 
        [](Texture2D* ptr) {
            UnloadTexture(*ptr);
            delete ptr;
        });

    m_textures[fileName] = sharedTexture;
    return sharedTexture;
}
