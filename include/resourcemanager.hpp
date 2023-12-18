#ifndef RESOURSEMANAGER_HPP
#define RESOURSEMANAGER_HPP

#include <map>
#include <stdexcept>
#include <SFML/Graphics/Texture.hpp>
#include <string>


class ResourceManager {
private:
    static ResourceManager* resourceManager;
    ResourceManager() {};
    std::map<std::string, sf::Texture> textures;
    
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    static ResourceManager* getInstance();
    sf::Texture& getTexture(const std::string& filename);
};

#endif // RESOURSEMANAGER_HPP