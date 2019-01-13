#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include "texture_manager.hpp"

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
    sf::Texture tex;
    tex.loadFromFile(filename);
    this->textures[name] = tex;
    return;
}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
    std::cout<<"texture: "<<texture<<std::endl;
    return this->textures.at(texture);
}
