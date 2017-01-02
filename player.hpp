#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "animation_handler.hpp"
#include "hit_list.hpp"


enum PlayerState{LEFT,RIGHT,STAND};

class Player
{
public:
    PlayerState playerState;
    sf::Vector2f velocity;
    HitList hitList;
    float speed;
    float jumpPower;
    unsigned int health;
    unsigned int damage;
    AnimationHandler animHandler;
    sf::Sprite sprite;

    void setStats(const unsigned int health,const unsigned int damage,
                  const std::vector<Animation>& animations,const sf::Texture& texture);

    void update(const float dt);
    void draw(sf::RenderWindow& window,const float dt);
    void turn(PlayerState pS);
    void jump();
    void makeMove(bool collision);
    sf::FloatRect getRect();
    void getHit(const int& ammout);

};
#endif // PLAYER_HPP
