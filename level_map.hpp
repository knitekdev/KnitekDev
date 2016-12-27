#ifndef LEVEL_MAP_HPP
#define LEVEL_MAP_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "animation_handler.hpp"


enum ObjectType{BACKGROUND,PLATFORM};

class Object
{
public:
    AnimationHandler animHandler;
    sf::Sprite sprite;
    ObjectType objectType;
    int animVariant;
    Object(const sf::Vector2f position,
           const unsigned int width, const unsigned int height, const sf::Texture& texture,
           const std::vector<Animation>& animations, const ObjectType objectType, const int animVariant)
           {
               this->sprite.setTexture(texture);
               this->sprite.setPosition(position);
               this->animVariant = animVariant;
               this->objectType = objectType;
               this->animHandler.frameSize = sf::IntRect(0,0,width,height);
               for(auto animation : animations)
               {
                    this->animHandler.addAnim(animation);
               }
               this->animHandler.update(0.0f);
           }
};

class LevelMap
{
public:
    std::vector<Object> objectList;
    void update(float dt);
    void draw(sf::RenderWindow& window, float dt);
    void addObject(Object object);
};
#endif // LEVEL_MAP_HPP
