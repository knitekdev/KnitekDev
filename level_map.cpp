#include "level_map.hpp"
#include <iostream>
void LevelMap::update(float dt)
{

}

bool LevelMap::collision(sf::Sprite& objectin, sf::Vector2f& velocity)
{
    sf::Sprite object = objectin;
    object.move(velocity);

    if(object.getPosition().x<0 || object.getPosition().x + object.getGlobalBounds().width > 1280)velocity.x=0;

    if(!this->platformList.empty())
    for(unsigned int i = 0; i < platformList.size(); i++)
    {
        if(platformList.at(i).intersects(object.getGlobalBounds()))
        {
            if(velocity.y>=0)
            {
                if(platformList.at(i).top < object.getGlobalBounds().top + object.getGlobalBounds().height)
                {

                    objectin.move(velocity.x,0);

                    if(((platformList.at(i).left < objectin.getGlobalBounds().left + objectin.getGlobalBounds().width) ||
                        (platformList.at(i).left + platformList.at(i).width > objectin.getGlobalBounds().left))&&
                        (platformList.at(i).top < objectin.getGlobalBounds().top + objectin.getGlobalBounds().height))

                    {
                        objectin.move(0,velocity.y);
                        return true;
                    }
                    else
                    {
                        velocity.y=0;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void LevelMap::draw(sf::RenderWindow& window, float dt)
{
    if(!this->objectList.empty())
    {
        for(unsigned int i = 0; i<this->objectList.size(); i++)
        {
            this->objectList.at(i).animHandler.changeAnim(this->objectList.at(i).animVariant);
            this->objectList.at(i).animHandler.update(dt);
            this->objectList.at(i).sprite.setTextureRect(this->objectList.at(i).animHandler.bounds);
            window.draw(this->objectList.at(i).sprite);
        }
    }
}

void LevelMap::addObject(Object object)
{
    objectList.push_back(object);
    return;
}

void LevelMap::addPlatform(sf::FloatRect platform)
{
    platformList.push_back(platform);
    return;
}
