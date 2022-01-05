#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const char* fileName) {
    string filePath = "images/";
    filePath += fileName;
    filePath += ".png";

    textures[fileName].loadFromFile(filePath);
}

sf::Texture& TextureManager::GetTexture(const char* texKey) {
    if (textures.find(texKey) == textures.end()) {
        LoadTexture(texKey);
    }
    return textures[texKey];
}
void TextureManager::Clear() {
    textures.clear();
}