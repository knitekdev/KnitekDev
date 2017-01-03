#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "animation_handler.hpp"
#include "hit_list.hpp"
#include "hp_bar.hpp"
#include "attack.hpp"


enum PlayerState{LEFT,RIGHT,STAND};

class Player
{
public:
    PlayerState playerState;
    PlayerState lastplayerState;
    sf::Vector2f velocity;
    HitList hitList;
    Hp_Bar hpBar;
    Projectile projectile;
    float speed;
    float jumpPower;
    int health;
    int maxhealth;
    int damage;
    AnimationHandler animHandler;
    sf::Sprite sprite;

    void setStats(const std::vector<Animation>& animations,const sf::Texture& texture, const sf::Texture& soapTX);
    void load(int health, int damage);

    void update(const float dt);
    void draw(sf::RenderWindow& window,const float dt);
    void turn(PlayerState pS);
    void jump();
    void makeMove(bool collision);
    sf::FloatRect getRect();
    void getHit(const int& ammout);
    Projectile pushAttack();

};
#endif // PLAYER_HPP
