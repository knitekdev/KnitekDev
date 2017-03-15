#include "attack.hpp"

bool Projectile::checkrange()
{
    if(sprite.getGlobalBounds().left - startx > range)return true;
    if(sprite.getGlobalBounds().left - startx < (range * -1)) return true;
    if(velocity.x==0)
        if(sprite.getGlobalBounds().top - starty > range) return true;
    return false;
}
void Projectile::moveSprite(const float dt)
{
    float gravity = (sprite.getGlobalBounds().left - startx)*dt*0.02;
    if(gravity<0) gravity *= -1;
    if(velocity.x==0)gravity=0.02;
    sprite.move(sf::Vector2f(velocity.x * dt, velocity.y * gravity));
}

void Attack::addAttack(const sf::Texture& texture, sf::Vector2f& position, sf::Vector2f velocity, int range, int damage, int owner)
{
    attacks.push_back(Projectile(texture,position,velocity,range,damage,owner));
}

void Attack::addAttack(const Projectile& pro)
{
    attacks.push_back(pro);
}



void Attack::update(const float dt)
{
    if(!attacks.empty())
    {
        for(unsigned int i = 0; i<attacks.size(); i++)
        {
            if(attacks[i].checkrange())
            {
                attacks.erase(attacks.begin()+i);
                if(attacks.empty())return;
                i--;
            }
        }
    }
    if(!attacks.empty())
    {
        for(unsigned int i = 0; i<attacks.size(); i++)
        {
            attacks[i].moveSprite(dt);
            //attacks[i].sprite.rotate(360*dt*3); //obracanie siê

        }
    }
}

void Attack::draw(sf::RenderWindow& window)
{
    if(!attacks.empty())
    {
        for(unsigned int i = 0; i<attacks.size(); i++)
        {
            window.draw(attacks[i].sprite);
        }
    }
}

int Attack::check(sf::FloatRect playerRect, int ofiara)
{
    if(!attacks.empty())
    {
        for(unsigned int i=0; i<attacks.size(); i++)
        {
            if(playerRect.intersects(attacks[i].sprite.getGlobalBounds()))
                if(attacks[i].owner != ofiara)
                {
                    int smieszek = attacks[i].damage;
                    attacks.erase(attacks.begin()+i);
                    return smieszek;
                }
        }
    }
    return 0;
}


