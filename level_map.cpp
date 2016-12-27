#include "level_map.hpp"
void LevelMap::update(float dt)
{

}


void LevelMap::draw(sf::RenderWindow& window, float dt)
{
    for(auto object : objectList)
    {
        if(object.objectType == PLATFORM)continue;
        object.animHandler.changeAnim(object.animVariant);
        object.animHandler.update(dt);
        object.sprite.setTextureRect(object.animHandler.bounds);
        window.draw(object.sprite);
    }
}

void LevelMap::addObject(Object object)
{
    objectList.push_back(object);
    return;
}
