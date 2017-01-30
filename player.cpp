#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <iostream>
#include <cstdlib>

void Player::makeMove(bool collision)
{


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
    //sprawdzanie czy jakis pocisk nie trafi³ gracza
    getHit(attackList->check(sprite.getGlobalBounds(),0) * -1);

    static float turnboost = 6;
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
            lastplayerState = LEFT;
            break;
        }
    case RIGHT:
        {
            if(velocity.x >0)turnboost = 2;
            if(velocity.x < speed)velocity.x +=speed * dt * 1.5f * turnboost;
            lastplayerState = RIGHT;
            break;
        }
    }
    velocity.y +=speed * 2.5f * dt;

    hitList.update(dt);
    hpBar.update(maxhealth,health);
    attSpeedtimer+=dt;

//    if(!levelMap->collision(sprite,velocity))
//    {
//        sprite.move(velocity);
//    }
    levelMap->playercollision(sprite,velocity);
}

void Player::getHit(const int& ammout)
{
    if(ammout!=0)
    {
        int hp = health;
        if(health+ammout < 0)health+=ammout-health;
        else if(health+ammout > maxhealth) health+= maxhealth - health;
        else health+=ammout;
        if(ammout<0)
        {
//       do zmiany     velocity.x = (velocity.x * -1) + 5;

            if(velocity.y>-1)velocity.y += -5;
            hitList.addHit(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2 + ((std::rand()%21)+1)-10,
                                        sprite.getGlobalBounds().top - 5 - ((std::rand()%16)+1)),ammout,sf::Color::Red);
        }
        else
            hitList.addHit(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2 + ((std::rand()%21)+1)-10,
                                        sprite.getGlobalBounds().top - 5 - ((std::rand()%16)+1)),ammout,hp!=health ? sf::Color::Green : sf::Color::Black);
    }
}


Projectile Player::pushAttack()
{
    if(attSpeedtimer>attSpeed)
    {
        attSpeedtimer = 0;
        Projectile projectilee = projectile;
        if(lastplayerState == LEFT)
        {
            projectilee.velocity.x *= -1;
            projectilee.sprite.setPosition(sf::Vector2f(sprite.getGlobalBounds().left - projectile.sprite.getGlobalBounds().width + 20,
                                                   sprite.getGlobalBounds().top + sprite.getGlobalBounds().height/2 - 20));
            projectilee.startx = sprite.getGlobalBounds().left - projectile.sprite.getGlobalBounds().width + 20;

        }
        else
        {
            projectilee.sprite.setPosition(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 20,
                                                   sprite.getGlobalBounds().top + sprite.getGlobalBounds().height/2 - 20));
            projectilee.startx = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 20;
        }
        return projectilee;
    }
}


void Player::load(std::string nr, TextureManager& texmgr, LevelMap *levelMap, Attack *attackList)
{
    srand(time(NULL));
    this->levelMap = levelMap;
    this->attackList = attackList;
    playerState = STAND;
    std::string name,tmp1,tmp2;
    std::fstream plik;
    name="data\\level\\player_level_"+nr+".dat";
    float x,y,width,height,x1,y1,duration;
    int animationnumber,range,damage,owner,framestart,frameend,ix,iy,iwidth,iheight;
    plik.open(name,std::ios::in);
    plik>>health;
    maxhealth = health;
    plik>>x;
    plik>>y;
    plik>>tmp1;
    plik>>tmp2;
    hpBar.setSprites(texmgr.getRef(tmp1),texmgr.getRef(tmp2),sf::Vector2f(x,y),sf::Vector2f(x+5,y-2));
    plik>>attSpeed;
    attSpeedtimer = 0;
    plik>>speed;
    plik>>jumpPower;
    plik>>x;
    plik>>y;
    velocity = sf::Vector2f(x,y);
    plik>>tmp1;
    sprite.setTexture(texmgr.getRef(tmp1));
    plik>>ix; plik>>iy; plik>>iwidth; plik>>iheight;
    animHandler.frameSize = sf::IntRect(ix,iy,iwidth,iheight);
    plik>>animationnumber;
    for(int j=0; j<animationnumber; j++)
    {
        plik>>framestart;
        plik>>frameend;
        plik>>duration;
        Animation animm(framestart,frameend,duration);
        animHandler.addAnim(animm);
    }
    animHandler.update(0.0f);
    plik>>tmp1; plik>>x; plik>>y; plik>>x1; plik>>y1; plik>>range; plik>>damage; plik>>owner;
    projectile = Projectile(texmgr.getRef(tmp1),sf::Vector2f(x,y),sf::Vector2f(x1,y1),range,damage,owner);
    plik.close();
}


