#ifndef HIT_LIST_HPP
#define HIT_LIST_HPP


#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

class Hit
{
public:
    sf::Text text;
    float lifetime;
    Hit(){}
    Hit(int wartosc, sf::Vector2f pos, sf::Font& font, sf::Color color)
    {
        this->lifetime = 0;
        this->text.setFont(font);
        this->text.setCharacterSize(20);
        this->text.setPosition(pos);
        this->text.setFillColor(color);
        this->text.setString(std::to_string(wartosc));
    }
    Hit(int wartosc, sf::Vector2f pos, sf::Font& font)
    {
        this->lifetime = 0;
        this->text.setFont(font);
        this->text.setCharacterSize(20);
        this->text.setPosition(pos);
        this->text.setFillColor(sf::Color::Red);
        this->text.setString(std::to_string(wartosc));
    }
};


class HitList
{
public:
    sf::Font font;
    std::vector<Hit> hits;
    float maxlifetime;
    HitList()
    {
        font.loadFromFile("data\\text\\arial.ttf");
        maxlifetime = 2;
    }
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void addHit(sf::Vector2f pos, int wartosc, sf::Color color);
};


#endif // HIT_LIST_HPP
