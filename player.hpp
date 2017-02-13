#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "texture_manager.hpp"
#include "animation_handler.hpp"
#include "hit_list.hpp"
#include "hp_bar.hpp"
#include "attack.hpp"
#include "level_map.hpp"
#include "defines.hpp"

class Player
{
    LevelMap *levelMap;
    Attack *attackList;
public:

    PlayerState playerState;
    PlayerState lastplayerState;
    sf::Vector2f velocity;
    HitList hitList;
    Hp_Bar hpBar;
    Projectile projectile;
    float speed;
    float jumpPower;
    float attSpeed;
    float attSpeedtimer;
    int health;
    int maxhealth;
    AnimationHandler animHandler;
    sf::Sprite sprite;

    void load(std::string nr, TextureManager& texmgr, LevelMap *levelMap, Attack *attackList);

    void update(const float dt);
    void draw(sf::RenderWindow& window,const float dt);
    void turn(PlayerState pS);
    void jump();
    void makeMove(bool collision);
    sf::FloatRect getRect();
    void getHit(const int& ammout);
    void pushAttack();

};
#endif // PLAYER_HPP
