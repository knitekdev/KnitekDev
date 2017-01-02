#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <iostream>
#include <cstdlib>
void Player::setStats(const std::vector<Animation>& animations, const sf::Texture& texture)
{
    srand(time(NULL));
    this->playerState = STAND;
    this->speed = 8;
    this->jumpPower = -8;
    this->velocity = sf::Vector2f(0,0);
    this->health = health;
    this->damage = damage;
    this->sprite.setTexture(texture);
    this->animHandler.frameSize = sf::IntRect(0,0,40,80);
    for(auto animation : animations)
    {
        this->animHandler.addAnim(animation);
    }
    this->animHandler.update(0.0f);
}

void Player::makeMove(bool collision)
{
    if(!collision)
    {
        sprite.move(velocity);
    }

}

void Player::turn(PlayerState ps)
{
    this->playerState = ps;
}

void Player::jump()
{
    if(velocity.y == 0.0f)
    {
        velocity.y +=jumpPower;
    }

}

void Player::draw(sf::RenderWindow& window,const float dt)
{
    this->animHandler.changeAnim(this->playerState);
    this->animHandler.update(dt);
    this->sprite.setTextureRect(this->animHandler.bounds);
    window.draw(this->sprite);
    hitList.draw(window);
    return;
}

sf::FloatRect Player::getRect()
{
    return this->sprite.getGlobalBounds();
}

void Player::update(const float dt)
{
    float turnboost = 6;
    switch(playerState)
    {
    case STAND:
        {
            velocity.x = 0.0f;
            break;
        }
    case LEFT:
        {
            if(velocity.x <0)turnboost = 2;
            if(velocity.x > (speed * -1))velocity.x +=speed * dt * -1 * 1.5f * turnboost;
            break;
        }
    case RIGHT:
        {
            if(velocity.x >0)turnboost = 2;
            if(velocity.x < speed)velocity.x +=speed * dt * 1.5f * turnboost;
            break;
        }
    }
    velocity.y +=speed * 2.5f * dt;
    hitList.update(dt);
    hpBar.update(maxhealth,health);
}

void Player::getHit(const int& ammout)
{
    if(health+ammout >= 0 && health+ammout <= maxhealth)
    {
        health+=ammout;
        if(ammout<0)
        hitList.addHit(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2 + ((std::rand()%21)+1)-10,
                                    sprite.getGlobalBounds().top - 5 - ((std::rand()%16)+1)),ammout,sf::Color::Red);
        else
        hitList.addHit(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2 + ((std::rand()%21)+1)-10,
                                    sprite.getGlobalBounds().top - 5 - ((std::rand()%16)+1)),ammout,sf::Color::Green);
    }
}
void Player::load(int health, int damage)
{
    this->maxhealth = health;
    this->health = health;
    this->damage = damage;
}
