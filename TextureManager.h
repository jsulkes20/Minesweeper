#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>

using std::unordered_map;
using std::string;


class TextureManager {
private:
    static unordered_map<string, sf::Texture> textures;
public:
    static void LoadTexture(const char* fileName);
    static sf::Texture& GetTexture(const char* texKey);
    static void LoadAllTextures();
    static void Clear();
};