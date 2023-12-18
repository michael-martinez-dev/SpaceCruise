#include "resourcemanager.hpp"

ResourceManager* ResourceManager::resourceManager;

ResourceManager* ResourceManager::getInstance() {
  if (resourceManager == nullptr) {
    resourceManager = new ResourceManager();
  }
  return resourceManager;
}

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
  auto it = textures.find(filename);
  if (it == textures.end()) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
      throw std::runtime_error("Failed to load texture: " + filename);
    }
    textures[filename] = texture;
  }
  return textures[filename];
}
