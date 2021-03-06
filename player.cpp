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

void Player::make_jump()
{
    if(velocity.y == 0.0f)
    jump=true;
}

void Player::draw(sf::RenderWindow& window,const float dt)
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

void Player::update(const float dt)
{
    //sprawdzanie czy jakis pocisk nie trafi� gracza
    getHit(attackList->check(sprite.getGlobalBounds(),0) * -1);

    //skacz
    if(jump /*&& velocity.y == 0.0f*/)
    {
        velocity.y +=jumpPower; //* (*gameSpeed);
        jump=false;
    }

    static float turnboost = 2;
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
            if(velocity.x > (speed * -1))
                velocity.x +=speed * dt * -1 * 1.5f * turnboost;
//                velocity.x = speed * dt * -35;
            lastplayerState = LEFT;
            break;
        }
    case RIGHT:
        {
            if(velocity.x >0)turnboost = 2;
            if(velocity.x < speed)
                velocity.x +=speed * dt * 1.5f * turnboost;
//                velocity.x = speed * dt * 35;
            lastplayerState = RIGHT;
            break;
        }
    }
    velocity.y +=speed * dt * 2.5f;
//    velocity.y =speed * dt * 35;
    hpBar.update(maxhealth,health);
    attSpeedtimer+=dt;
    attSpeedtimer+=dt;

    levelMap->playercollision(sprite,velocity,dt);
    getHit(levelMap->playercollisionTRAP(sprite));
}

void Player::getHit(const int &ammout)
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

            if(velocity.y>-1)
                velocity.y += -350;
            hitList->addHit(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2 + ((std::rand()%21)+1)-10,
                                        sprite.getGlobalBounds().top - 5 - ((std::rand()%16)+1)),ammout,sf::Color::Red);
        }
        else
            hitList->addHit(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2 + ((std::rand()%21)+1)-10,
                                        sprite.getGlobalBounds().top - 5 - ((std::rand()%16)+1)),ammout,hp!=health ? sf::Color::Green : sf::Color::Black);

        this->soundHandler.playRandomSound();
    }
}


void Player::pushAttack()
{
    if(attSpeedtimer>attSpeed)
    {
        attSpeedtimer = 0;
        if(lastplayerState == RIGHT && projectile.velocity.x < 0) projectile.velocity.x*=-1;
        if(lastplayerState == LEFT && projectile.velocity.x > 0) projectile.velocity.x*=-1;

        if(lastplayerState == LEFT)
        {
            projectile.sprite.setPosition(sf::Vector2f(sprite.getGlobalBounds().left+ projectile.spos.x
                                                       ,sprite.getGlobalBounds().top+projectile.spos.y));
        }
        else
        {
            projectile.sprite.setPosition(sf::Vector2f((sprite.getGlobalBounds().left + (sprite.getGlobalBounds().width)) - projectile.spos.x
                                                       ,sprite.getGlobalBounds().top+projectile.spos.y));
        }
        projectile.startx = projectile.sprite.getGlobalBounds().left;
        attackList->addAttack(projectile);
    }
}

void Player::moveDown()
{
    if((sprite.getGlobalBounds().height+sprite.getGlobalBounds().top)<lowesty)
    {
        sprite.move(0,1);
    }
}

void Player::load(std::string nr, TextureManager& texmgr, LevelMap *levelMap, Attack *attackList,HitList *hitList, SoundManager& soundMgr)
{
    jump = false;
    srand(time(NULL));
    this->levelMap = levelMap;
    this->attackList = attackList;
    this->hitList = hitList;
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
    plik>>lowesty;
    plik.close();

    int soundcount = 3;
    //plik>>soundcount;
    std::string soNames[3] = {"okrzyk1","okrzyk2","okrzyk3"};
    std::vector<Korek_Sound> tmpSounds;
    for(int i = 0;i<soundcount;i++)
    {
        //plik>>tmp1;
        tmpSounds.push_back(soundMgr.getRef(soNames[i]));
        //tmpSounds[i].getSound().play();
        //soundMgr.getRef(tmp1);
    }
    this->soundHandler = SoundHandler(tmpSounds,soundcount);

}


SoundHandler::SoundHandler()
{
    return;
}
SoundHandler::SoundHandler(std::vector<Korek_Sound> sounds,int soundCount)
{
    //this->sounds = new Korek_Sound[soundCount];
    //for(int i = 0; i<soundCount; i++)
     //   this->sounds[i] = sounds[i];
    this->soundCount = soundCount;
    this->sounds = sounds;
    return;
}

void SoundHandler::playRandomSound()
{
    int number = rand() % this->soundCount;
    sounds[number].play();
    std::cout<<"sdflk"<<std::endl;
    return;
}

SoundHandler::~SoundHandler()
{
    sounds.clear();
}



