#include "hp_bar.hpp"
#include <iostream>
void Hp_Bar::update(int maxhp, int hp)
{
    float currenthp = (float)hp*100 / (float)maxhp;
    sf::IntRect rect = hpSprite.getTextureRect();
    rect.width = (int)((border.getTextureRect().width-10) *(currenthp/100));
    this->hpSprite.setTextureRect(rect);
}

void Hp_Bar::draw(sf::RenderWindow& window)
{
    window.draw(border);
    window.draw(hpSprite);
}

void Hp_Bar::setSprites(sf::Texture& borderTX, sf::Texture& hpSpriteTX, sf::Vector2f borderPos, sf::Vector2f hpSpritePos)
{
    this->border.setTexture(borderTX);
    this->border.setPosition(borderPos);
    this->hpSprite.setTexture(hpSpriteTX);
    this->hpSprite.setPosition(hpSpritePos);
}
