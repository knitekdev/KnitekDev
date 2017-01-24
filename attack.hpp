#ifndef ATTACK_HPP
#define ATTACK_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
class Projectile
{
public:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    int startx;
    int range;
    int damage;
    int owner;
    Projectile(){}
    Projectile(const sf::Texture& texture,sf::Vector2f position, sf::Vector2f velocity, int range,
               int damage, int owner)
               {
                   this->sprite.setTexture(texture);
                   this->sprite.setPosition(position);
                   this->velocity = velocity;
                   this->startx = position.x;
                   this->range = range;
                   this->damage = damage;
                   this->owner = owner;
               }
    bool checkrange();
    void moveSprite(const float dt);
};


class Attack
{
public:
    std::vector<Projectile> attacks;
    void addAttack(const sf::Texture& texture, sf::Vector2f& position, sf::Vector2f velocity, int range, int damage, int owner);
    void addAttack(const Projectile& pro);
    void update(const float dt);
    void draw(sf::RenderWindow& window);
    int check(sf::FloatRect playerRect, int ofiara);
};

#endif // ATTACK_HPP
