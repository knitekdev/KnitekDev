#include "monster_manager.hpp"

void Monster::getHit(const int& ammount,HitList* hitList)
{
    if(ammount!=0)
    {
        hitList->addHit(sf::Vector2f(sprite.getGlobalBounds().left+5,sprite.getGlobalBounds().top-1),
                        (health-ammount<0)?(-(ammount-health)):(-(ammount)),sf::Color::Red);
        health-=ammount;
    }
}

void Monster::makeAttack(Attack *att)
{
    //odwracanie predkosci pocisku do kierunku ruchu
    if(monsterState == RIGHT && projectile.velocity.x < 0) projectile.velocity.x*=-1;
    if(monsterState == LEFT && projectile.velocity.x > 0) projectile.velocity.x*=-1;

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

void Monster::update(float playerX, const float &dt, Attack *att, LevelMap *levelMap)
{
    std::srand(time(NULL));
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


        // poruszaj potworem jeœli jego typ ró¿ny od statycznego
        if(monsterType!=3)
            if(!levelMap->monstercollision(sprite,velocity,dt,monsterState,monsterType))
            {
                sprite.move(0,velocity.y*dt);
            }

        //jeœli typ œledz¹cy to odwracaj za graczem
        if(monsterType==2 || monsterType ==5)
            if(playerX > (sprite.getGlobalBounds().left+10) && monsterState==LEFT)
                {
                    monsterState = RIGHT;
                }
            else if(playerX < (sprite.getGlobalBounds().left-10) && monsterState==RIGHT)
                {
                    monsterState = LEFT;
                }

        attacktimer+=dt;
        if(monsterType >= 1 && monsterType <= 3)
        {
            if(attacktimer>attackspeed)
            {
                attacktimer=0;
                makeAttack(att);
            }
        }
        else
        {
            if(attacktimer>attackSPD)
            {
                attackSPD =attackspeed - ((float)(std::rand()%(int)(attackspeed*10))/10);
                attacktimer=0;
                makeAttack(att);
            }
        }
    }
}

void Monster::draw(sf::RenderWindow& window, const float &dt)
{
    this->animHandler.changeAnim(this->monsterState);
    this->animHandler.update(dt);
    this->sprite.setTextureRect(this->animHandler.bounds);
    window.draw(this->sprite);

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
            if(monsters.at(i).health <= 0 || monsters.at(i).sprite.getGlobalBounds().top > 750)
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
            monsters[i].getHit(att->check(monsters[i].sprite.getGlobalBounds(),1),hitList);
            monsters[i].update(playerX,dt,att,levelMap);
        }
    }
}

void MonsterManager::load(std::string nr, TextureManager& texmgr, LevelMap* levelMap, Attack* att, HitList* hitList)
{
    this->att = att;
    this->levelMap = levelMap;
    this->hitList = hitList;
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
        if(monsterType == 4 || monsterType == 5)
        {
            monsters.back().sprite.setScale(2.5f,2.5f);
        }

    }
    plik.close();
}




