#ifndef HP_BAR_HPP
#define HP_BAR_HPP

#include <SFML/Graphics.hpp>

class Hp_Bar
{
    sf::Sprite border;
    sf::Sprite hpSprite;
public:
    void update(int maxhp, int hp);
    void draw(sf::RenderWindow& window);
    void setSprites(sf::Texture& borderTX, sf::Texture& hpSrpriteTX, sf::Vector2f borderPos, sf::Vector2f hpSpritePos);
};

#endif // HP_BAR_HPP
