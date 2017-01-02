#include "hit.hpp"

void Hit::draw(sf::RenderWindow& window)
{
    window.draw(text);
}

void Hit::update(float dt)
{
    this->duration+=dt;
    this->text.move(sf::Vector2f(0,speed * dt * -1.0f));
    if(duration>maxtime)destroy = true;
}

HitList::HitList()
{
    font.loadFromFile("data\\text\\arial.ttf");
}

void HitList::draw(sf::RenderWindow& window)
{
    for(unsigned int i = 0; i < hitlist.size(); i++)
    {
        hitlist.at(i).draw(window);
    }
}

void HitList::update(float dt)
{

    for(unsigned int i = 0; i < hitlist.size(); i++)
    {
        if(hitlist.at(i).destroy)
        {
            hitlist.erase(hitlist.begin()+i);
        }
    }
    for(unsigned int i = 0; i < hitlist.size(); i++)
    {
        hitlist.at(i).update(dt);
    }
}

void HitList::addHit(const sf::Vector2f& startposition,const int& ammout)
{
    Hit hit(font,startposition,ammout);
    hitlist.push_back(hit);
}

