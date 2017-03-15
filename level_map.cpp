#include "level_map.hpp"
#include <iostream>

void LevelMap::update(float dt)
{
    checkHit();
}

int LevelMap::playercollisionTRAP(const sf::Sprite &sprite)
{
    if(!objecttrapList.empty())
    {
        for(unsigned int i=0; i<objecttrapList.size(); i++)
        {
            if(objecttrapList[i].animVariant == 0)
            {
                if(sprite.getGlobalBounds().intersects(objecttrapList[i].sprite.getGlobalBounds()))
                {
                    objecttrapList[i].animVariant = 1;
                    hitList->addHit(sf::Vector2f(objecttrapList[i].sprite.getGlobalBounds().left+5,objecttrapList[i].sprite.getGlobalBounds().top-5),(objecttrapList[i].hp),sf::Color::Cyan);
                    objecttrapList[i].hp = 0;
                    return -objecttrapList[i].damage;
                }
            }
        }
    }
    return 0;
}

void LevelMap::checkHit()
{
    //sprawdzanie czy obiekt oberwa³ pociskiem od gracza
    if(!activeobjectList.empty() && !attackList->attacks.empty())
    {
        for(unsigned int i=0; i<activeobjectList.size(); i++)
        {
            if(activeobjectList[i].animVariant==0)
            {
                for(unsigned int j=0; j<attackList->attacks.size(); j++)
                {
                    if(attackList->attacks[j].sprite.getGlobalBounds().intersects(activeobjectList[i].sprite.getGlobalBounds()))
                    if(attackList->attacks[j].owner==0)
                    {
                        activeobjectList[i].animVariant = 1;
                        objectList.push_back(hiddenobjectList[i]);
                        addPlatform(sf::FloatRect(sf::Vector2f(hiddenobjectList[i].sprite.getGlobalBounds().left,
                                                                hiddenobjectList[i].sprite.getGlobalBounds().top),
                                                    sf::Vector2f(hiddenobjectList[i].sprite.getGlobalBounds().width,
                                                                hiddenobjectList[i].sprite.getGlobalBounds().height)));
                    }
                }
            }
        }
    }

    if(!objecttrapList.empty() && !attackList->attacks.empty())
    {
        for(unsigned int i=0; i<objecttrapList.size(); i++)
        {
            if(objecttrapList[i].animVariant == 0 && objecttrapList[i].objectType == 4)
            {
                for(unsigned int j=0; j<attackList->attacks.size(); j++)
                {
                    if(attackList->attacks[j].owner == 0)
                    if(attackList->attacks[j].sprite.getGlobalBounds().intersects(objecttrapList[i].sprite.getGlobalBounds()))
                    {
                        if(objecttrapList[i].hp - attackList->attacks[j].damage <0)
                        {
                            hitList->addHit(sf::Vector2f(objecttrapList[i].sprite.getGlobalBounds().left+5,objecttrapList[i].sprite.getGlobalBounds().top-5),(objecttrapList[i].hp),sf::Color::Cyan);
                            objecttrapList[i].hp = 0;
                            objecttrapList[i].animVariant = 1;
                        }
                        else
                        {
                            hitList->addHit(sf::Vector2f(objecttrapList[i].sprite.getGlobalBounds().left+5,objecttrapList[i].sprite.getGlobalBounds().top-5),(attackList->attacks[j].damage),sf::Color::Cyan);
                            objecttrapList[i].hp -= attackList->attacks[j].damage;
                            attackList->attacks.erase(attackList->attacks.begin()+j);
                        }
                    }
                }
            }
        }
    }
}

bool LevelMap::playercollision(sf::Sprite& objectin, sf::Vector2f& velocityinN,float dt)
{
    sf::Sprite objecty = objectin;
    sf::Sprite objectx = objectin;
    sf::Vector2f velocityin = velocityinN * dt;
    objectx.move(velocityin.x,0);
    objecty.move(0,velocityin.y);
    if(objectx.getGlobalBounds().left < 0) velocityinN.x = 0;

    if(!this->platformList.empty())
    {
        for(unsigned int i=0; i<platformList.size(); i++)
        {
            if(velocityin.y>=0)
            {
                if(platformList[i].intersects(objecty.getGlobalBounds()))
                {
                    if((platformList[i].left < ((objectx.getGlobalBounds().left + objectx.getGlobalBounds().width)-15))&&
                       ((platformList[i].left+platformList[i].width)>(objectx.getGlobalBounds().left+15)))
                    if(!platformList[i].intersects(objectin.getGlobalBounds()))
                    {
                        velocityin.y = platformList[i].top - (objectin.getGlobalBounds().top + objectin.getGlobalBounds().height);
                        velocityinN.y = velocityin.y;
                        objectin.move(velocityin);
                        velocityinN.y = 0;
                        return true;
                    }
                }
            }
        }
    }
    objectin.move(velocityin);
    return false;
}

bool LevelMap::monstercollision(sf::Sprite& objectin, sf::Vector2f& velocityin,const float& dt, PlayerState &monsterState,const int &monsterType)
{
    sf::Sprite objectx = objectin;
    sf::Sprite objecty = objectin;
    sf::Vector2f velocity = velocityin * dt;
    objectx.move(velocity.x,0);
    objecty.move(0,velocity.y);
    float x=velocity.x,y=velocity.y;
    bool trigger = false;

//    if(objectx.getGlobalBounds().left<0 || objectx.getGlobalBounds().left + objectx.getGlobalBounds().width > 1280)x=0;

    if(!this->platformList.empty())
    {
        for(unsigned int i=0; i<platformList.size(); i++)
        {
            trigger = false;
//            if(platformList.at(i).intersects(objectx.getGlobalBounds()))
//            {
//                trigger = true;
//                if(platformList.at(i).left<objectx.getGlobalBounds().left)
//                    x = platformList.at(i).left - (objectin.getGlobalBounds().left + objectin.getGlobalBounds().width);
//                if(platformList.at(i).left + platformList.at(i).width > objectx.getGlobalBounds().left)
//                    x = objectin.getGlobalBounds().left - (platformList.at(i).left + platformList.at(i).width);
//            }
            if(platformList.at(i).intersects(objecty.getGlobalBounds()))
            {
                trigger = true;
                if(objecty.getGlobalBounds().top + objecty.getGlobalBounds().height > platformList.at(i).top
                   && objecty.getGlobalBounds().top< platformList.at(i).top + platformList.at(i).height)
                    y = platformList.at(i).top - (objectin.getGlobalBounds().top + objectin.getGlobalBounds().height);
            }

            //zmiana kierunku gdy konczy sie platforma
            if((monsterType != 3) && trigger && ((platformList.at(i).left > objectx.getGlobalBounds().left) ||
                           (platformList.at(i).left + platformList.at(i).width < objectx.getGlobalBounds().left + objectx.getGlobalBounds().width)))
            {
                if(velocityin.x<0)monsterState = RIGHT; else monsterState = LEFT;
                x=0;
            }
            if(trigger)
            {
                objectin.move(x,y);
                return true;
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
    if(!this->activeobjectList.empty())
    {
        for(unsigned int i=0; i<this->activeobjectList.size(); i++)
        {
            this->activeobjectList.at(i).animHandler.changeAnim(this->activeobjectList.at(i).animVariant);
            this->activeobjectList.at(i).animHandler.update(dt);
            this->activeobjectList.at(i).sprite.setTextureRect(this->activeobjectList.at(i).animHandler.bounds);
            window.draw(this->activeobjectList.at(i).sprite);
        }
    }
    if(!this->objecttrapList.empty())
    {
        for(unsigned int i=0; i<this->objecttrapList.size(); i++)
        {
            this->objecttrapList.at(i).animHandler.changeAnim(this->objecttrapList.at(i).animVariant);
            this->objecttrapList.at(i).animHandler.update(dt);
            this->objecttrapList.at(i).sprite.setTextureRect(this->objecttrapList.at(i).animHandler.bounds);
            window.draw(this->objecttrapList.at(i).sprite);
        }
    }
}

void LevelMap::addObject(Object object)
{
    objectList.push_back(object);
    return;
}

void LevelMap::addactiveObject(Object object)
{
    activeobjectList.push_back(object);
    return;
}
void LevelMap::addhiddenObject(Object object)
{
    hiddenobjectList.push_back(object);
    return;
}

void LevelMap::addtrapObject(ObjectTrap object)
{
    objecttrapList.push_back(object);
    return;
}

void LevelMap::addPlatform(sf::FloatRect platform)
{
    platformList.push_back(platform);
    return;
}
