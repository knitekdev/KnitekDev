#include "monster_manager.hpp"

void Monster::getHit(int ammount)
{
    if(ammount!=0)
    {
        hitList.addHit(sf::Vector2f(sprite.getGlobalBounds().left+5,sprite.getGlobalBounds().top-1),-ammount,sf::Color::Red);
        health-=ammount;
    }
}

void Monster::update(float playerX, const float &dt, Attack *att, LevelMap *levelMap)
{
    int range = sprite.getGlobalBounds().left - playerX; range *= (range<0)? -1 : 1;
    if(range < viewrange)
    {
        attacktimer+=dt;
        switch(monsterState)
        {
        case LEFT:
            {
                if(velocity.x > 0) {velocity.x *= -1; projectile.velocity.x *= -1;}
                break;
            }
        case RIGHT:
            {
                if(velocity.x <0) {velocity.x *= -1; projectile.velocity.x *= -1;}
                break;
            }
        }
//        if(playerX > sprite.getGlobalBounds().left)
//        {
//            monsterState = RIGHT;
//        }
//        else
//        {
//            monsterState = LEFT;
//        }

        if(!levelMap->monstercollision(sprite,velocity,dt,monsterState))
            sprite.move(0,velocity.y*dt);

        if(attacktimer>attackspeed)
        {
            if(monsterState == RIGHT && projectile.velocity.x < 0) projectile.velocity.x*=-1;
            if(monsterState == LEFT && projectile.velocity.x > 0) projectile.velocity.x*=-1;
            attacktimer=0;
            projectile.sprite.setPosition(sf::Vector2f(sprite.getGlobalBounds().left,sprite.getGlobalBounds().top));
            projectile.startx = sprite.getGlobalBounds().left;

            att->addAttack(projectile);
        }
    }
    hitList.update(dt);
}

void Monster::draw(sf::RenderWindow& window, const float &dt)
{
    this->animHandler.changeAnim(this->monsterState);
    this->animHandler.update(dt);
    this->sprite.setTextureRect(this->animHandler.bounds);
    window.draw(this->sprite);
    hitList.draw(window);
}


//======================================================================================
void MonsterManager::draw(sf::RenderWindow& window, const float &dt)
{
    if(!monsters.empty())
    {
        for(unsigned int i=0; i<monsters.size(); i++)
        {
            monsters[i].draw(window,dt);
        }
    }
}

void MonsterManager::update(float playerX, const float &dt)
{
    if(!monsters.empty())
    {
        for(unsigned int i = 0; i<monsters.size(); i++)
        {
            if(monsters.at(i).health <= 0)
            {
                monsters.erase(monsters.begin()+i);
                if(monsters.empty()) return;
                i--;
            }
        }
    }
    if(!monsters.empty())
    {
        for(unsigned int i=0; i<monsters.size(); i++)
        {
            monsters[i].getHit(att->check(monsters[i].sprite.getGlobalBounds(),1));
            monsters[i].update(playerX,dt,att,levelMap);
        }
    }
}

void MonsterManager::load(std::string nr, TextureManager& texmgr, LevelMap* levelMap, Attack* att)
{
    this->att = att;
    this->levelMap = levelMap;
    std::fstream plik;
    std::string name="data\\level\\monsters_level_"+nr+".dat";
    std::string texname;
    plik.open(name,std::ios::in);
    float x,x1,y,y1,duration,viewRange,attackSpeed;
    int health,animNumber,startFrame,endFrame,animVariant,monsterType,range,damage,owner,monsterNumber;
    unsigned int width, height;
    plik>>monsterNumber;
    if(!monsterNumber)return;
    for(int i=0; i<monsterNumber; i++)
    {
        std::vector<Animation> animations;
        plik>>health;
        plik>>x; plik>>y;
        plik>>texname;
        plik>>x1; plik>>y1;
        plik>>animNumber;
        for(int j=0; j<animNumber; j++)
        {
            plik>>startFrame; plik>>endFrame; plik>>duration;
            animations.push_back(Animation(startFrame,endFrame,duration));
        }
        if(animNumber == 0)animations.push_back(Animation(0,0,1.0f));
        plik>>animVariant;
        plik>>width; plik>>height;
        plik>>viewRange; plik>>attackSpeed; plik>>monsterType;
        monsters.push_back(Monster(health,sf::Vector2f(x,y),texmgr.getRef(texname),sf::Vector2f(x1,y1),animations,animVariant,
                                   width,height,viewRange,attackSpeed,monsterType));

        plik>>texname;
        plik>>x; plik>>y; plik>>x1; plik>>y1;
        plik>>range;
        plik>>damage;
        plik>>owner;
        monsters.back().projectile = Projectile(texmgr.getRef(texname),sf::Vector2f(x,y),sf::Vector2f(x1,y1),range,damage,owner);
    }
    plik.close();
}




