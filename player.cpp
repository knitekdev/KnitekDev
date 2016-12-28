#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <iostream>
void Player::setStats(const unsigned int health, const unsigned int damage,
                      const std::vector<Animation>& animations, const sf::Texture& texture)
{
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

void Player::draw(sf::RenderWindow& window, float dt)
{
    this->animHandler.changeAnim(this->playerState);
    this->animHandler.update(dt);
    this->sprite.setTextureRect(this->animHandler.bounds);
    window.draw(this->sprite);
    return;
}

sf::FloatRect Player::getRect()
{
    return this->sprite.getGlobalBounds();
}

void Player::update(float dt)
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
}
