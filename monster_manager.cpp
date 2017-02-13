#include "monster_manager.hpp"

void Monster::getHit(const int &ammount)
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


        if(monsterType!=3)
            if(!levelMap->monstercollision(sprite,velocity,dt,monsterState))
            {
                sprite.move(0,velocity.y*dt);
            }

        if(monsterType==2)
            if(playerX > sprite.getGlobalBounds().left)
                {
                    monsterState = RIGHT;
                }
            else
                {
                    monsterState = LEFT;
                }

        attacktimer+=dt;
        if(attacktimer>attackspeed)
        {
            //odwracanie predkosci pocisku do kierunku ruchu
            if(monsterState == RIGHT && projectile.velocity.x < 0) projectile.velocity.x*=-1;
            if(monsterState == LEFT && projectile.velocity.x > 0) projectile.velocity.x*=-1;
            attacktimer=0;

            //ustawienie pozycji pocisku wzgledem obiektu z uwzglednieniem korekcji zawartej w pocisku (spos)
            if(monsterState == LEFT)
            {
                projectile.sprite.setPosition(sf::Vector2f(sprite.getGlobalBounds().left + projectile.spos.x
                                                       ,sprite.getGlobalBounds().top+projectile.spos.y));
            }
            else
            {
                projectile.sprite.setPosition(sf::Vector2f((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) - projectile.spos.x
                                                       ,sprite.getGlobalBounds().top+projectile.spos.y));
            }
            //ustalenie pozycji startowej pocisku do odmierzenia zasiegu ataku
            projectile.startx = projectile.sprite.getGlobalBounds().left;
            projectile.starty = projectile.sprite.getGlobalBounds().top;

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
        plik>>x; plik>>y;
        plik>>width; plik>>height;
        plik>>texname;
        plik>>health;
        plik>>x1; plik>>y1;
        plik>>animNumber;
        if(animNumber == 0)
        {
            animations.push_back(Animation(0,0,1.0f));
        }
        else
        {
            for(int j=0; j<animNumber; j++)
            {
                plik>>startFrame; plik>>endFrame; plik>>duration;
                animations.push_back(Animation(startFrame,endFrame,duration));
            }
        }
        plik>>animVariant;
        plik>>viewRange; plik>>attackSpeed; plik>>monsterType;
        monsters.push_back(Monster(sf::Vector2f(x,y),texmgr.getRef(texname),health,sf::Vector2f(x1,y1),animations,animVariant,
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




