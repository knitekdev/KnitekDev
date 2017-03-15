#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "level_map.hpp"
#include "texture_manager.hpp"
#include "animation_handler.hpp"
#include "hit_list.hpp"
#include "hp_bar.hpp"
#include "attack.hpp"
#include "defines.hpp"
#include "hit_list.hpp"

class Player
{
    LevelMap *levelMap;
    Attack *attackList;
    HitList *hitList;

public:
    float *gameSpeed;
    PlayerState playerState;
    PlayerState lastplayerState;
    sf::Vector2f velocity;
    Hp_Bar hpBar;
    Projectile projectile;
    float speed;
    float jumpPower;
    float attSpeed;
    float attSpeedtimer;
    int health;
    int maxhealth;
    float lowesty;
    bool jump;
    AnimationHandler animHandler;
    sf::Sprite sprite;

    void load(std::string nr, TextureManager& texmgr, LevelMap *levelMap, Attack *attackList, HitList *hitList);

    void update(const float dt);
    void draw(sf::RenderWindow& window,const float dt);
    void turn(PlayerState pS);
    void make_jump();
    void moveDown();
    void makeMove(bool collision);
    sf::FloatRect getRect();
    void getHit(const int& ammout);
    void pushAttack();

};
#endif // PLAYER_HPP
