#ifndef LEVEL_MAP_HPP
#define LEVEL_MAP_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "defines.hpp"
#include "animation_handler.hpp"
#include "attack.hpp"
#include "hit_list.hpp"



enum ObjectType{BACKGROUND,PLATFORM};

class Object
{
public:
    AnimationHandler animHandler;
    sf::Sprite sprite;
    ObjectType objectType;
    int animVariant;
    Object()
    {

    }
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

class ObjectTrap : public Object
{
public:
    int hp;
    int damage;
    ObjectTrap(const sf::Vector2f position,
           const unsigned int width, const unsigned int height, const sf::Texture& texture,
           const std::vector<Animation>& animations, const ObjectType objectType, const int animVariant, int hp, int damage)
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
               this->hp = hp;
               this->damage = damage;
           }
};

class LevelMap
{
public:
    Attack *attackList;
    HitList *hitList;
    std::vector<Object> objectList;
    std::vector<Object> activeobjectList;
    std::vector<Object> hiddenobjectList;
    std::vector<ObjectTrap> objecttrapList;
    std::vector<sf::FloatRect> platformList;
    void update(float dt);
    void checkHit();
    void draw(sf::RenderWindow& window, float dt);
    void addObject(Object object);
    void addactiveObject(Object object);
    void addhiddenObject(Object object);
    void addtrapObject(ObjectTrap object);
    void addPlatform(sf::FloatRect platform);
    bool collision(sf::Sprite& objectin,sf::Vector2f& velocity);
    bool monstercollision(sf::Sprite& objectin, sf::Vector2f& velocityin, const float &dt, PlayerState &monsterState, const int &monsterType);
    bool playercollision(sf::Sprite& objectin, sf::Vector2f& velocityin, float dt);
    int playercollisionTRAP(const sf::Sprite &sprite);
};
#endif // LEVEL_MAP_HPP
