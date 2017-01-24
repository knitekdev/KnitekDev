#include "attack.hpp"

bool Projectile::checkrange()
{
    if(sprite.getGlobalBounds().left - startx > range)return true;
    else if(sprite.getGlobalBounds().left - startx < (range * -1)) return true;
    else return false;
}
void Projectile::moveSprite(const float dt)
{
    float gravity = sprite.getGlobalBounds().left - startx;
    if(gravity<0) gravity *= -1;
    sprite.move(sf::Vector2f(velocity.x * dt, velocity.y * dt * gravity));
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
                    attacks.erase(attacks.begin()+i);
                    return attacks[i].damage;
                }
        }
    }
    return 0;
}


