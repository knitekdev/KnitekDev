#ifndef MONSTER_MANAGER_HPP
#define MONSTER_MANAGER_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "animation_handler.hpp"
#include "player.hpp"
#include "attack.hpp"
#include "level_map.hpp"
#include "hit_list.hpp"



class Monster
{
public:
    AnimationHandler animHandler;
    PlayerState monsterState;
    Projectile projectile;
//    HitList hitList;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    int health;
    float viewrange;
    float attackspeed;
    float attacktimer;
    int monsterType;

    Monster(){}
    Monster( const sf::Vector2f& position, const sf::Texture& texture,const int health, const sf::Vector2f& velocity,
            const std::vector<Animation>& animations,const int animVariant, const unsigned int width, const unsigned int height,
            const float viewrange, const float attackspeed, const int monsterType)
    {
        this->health = health;
        this->sprite.setTexture(texture);
        this->sprite.setPosition(position);
        this->velocity = velocity;
        this->monsterState = (PlayerState)animVariant;
        this->animHandler.frameSize = sf::IntRect(0,0,width,height);
        for(auto animation : animations)
        {
            this->animHandler.addAnim(animation);
        }
        this->animHandler.update(0.0f);

        this->monsterType = monsterType;
        this->viewrange = viewrange;
        this->attackspeed = attackspeed;
    }

    void update(float playerX, const float &dt, Attack *att, LevelMap *levelMap);
    void draw(sf::RenderWindow& window, const float &dt);
    void getHit(const int &ammount,HitList* hitList);
};


class MonsterManager
{
public:
    std::vector<Monster> monsters;
    LevelMap* levelMap;
    Attack* att;
    HitList* hitList;
    void update(float playerX, const float &dt);
    void draw(sf::RenderWindow& window, const float &dt);
    void load(std::string nr,TextureManager& texmgr, LevelMap* levelMap, Attack* att, HitList* hitList);
};


#endif // MONSTER_MANAGER_HPP
