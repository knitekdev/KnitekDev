#include "hit_list.hpp"

void HitList::draw(sf::RenderWindow& window)
{
    if(!hits.empty())
    for(unsigned int i = 0; i<hits.size(); i++)
    {
        window.draw(hits.at(i).text);
    }
}

void HitList::update(float dt)
{
    if(!hits.empty())
    {
        for(unsigned int i = 0; i<hits.size(); i++)
        {
            if(hits.at(i).lifetime > this->maxlifetime)
            {
                hits.erase(hits.begin()+i);
                if(hits.empty()) return;
                i--;
            }
        }
    }

    if(!hits.empty())
    {
        for(unsigned int i = 0; i<hits.size(); i++)
        {
            hits.at(i).lifetime += dt;
            hits.at(i).text.move(0,-1 * 45 * dt);
        }
    }
}

void HitList::addHit(sf::Vector2f pos, int wartosc,sf::Color color)
{
    hits.push_back(Hit(wartosc,pos,this->font,color));
}
