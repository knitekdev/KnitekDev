#ifndef HIT_HPP
#define HIT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class Hit
{
public:
    bool destroy;
    sf::Text text;
    float duration;
    float speed;
    float maxtime;

    Hit(const sf::Font font,const sf::Vector2f startPosition,
         const int ammout)
    {
        this->destroy = false;
        this->text.setFont(font);
        this->text.setCharacterSize(15);
        this->text.setPosition(startPosition);
        this->text.setFillColor(sf::Color::Red);
        this->text.setString(std::to_string(ammout));
        this->duration = 0.0f;
        this->speed = 5;
        this->maxtime = 2;
    }

    void update(float dt);
    void draw(sf::RenderWindow& window);
};

class HitList
{
public:
    sf::Font font;
    std::vector<Hit> hitlist;
    HitList();
//    ~HitList()
//    {
//        hitlist.clear();
//    }

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void addHit(const sf::Vector2f& startposition,const int& ammout);
};

#endif // HIT_HPP
