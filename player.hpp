#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "animation_handler.hpp"
#include "hit_list.hpp"
#include "hp_bar.hpp"


enum PlayerState{LEFT,RIGHT,STAND};

class Player
{
public:
    PlayerState playerState;
    sf::Vector2f velocity;
    HitList hitList;
    Hp_Bar hpBar;
    float speed;
    float jumpPower;
    int health;
    int maxhealth;
    int damage;
    AnimationHandler animHandler;
    sf::Sprite sprite;

    void setStats(const std::vector<Animation>& animations,const sf::Texture& texture);
    void load(int health, int damage);

    void update(const float dt);
    void draw(sf::RenderWindow& window,const float dt);
    void turn(PlayerState pS);
    void jump();
    void makeMove(bool collision);
    sf::FloatRect getRect();
    void getHit(const int& ammout);

};
#endif // PLAYER_HPP
