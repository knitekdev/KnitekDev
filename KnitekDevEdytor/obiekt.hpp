#ifndef OBIEKT_HPP
#define OBIEKT_HPP

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Obiekt
{
public:
    string nazwa;
    sf::Sprite sprite;
    string parametry;
    int type; //1 - obiekt swiata 2 - przeciwnik
    Obiekt()
    {}
    Obiekt(int x, int y, int width, int height,const sf::Texture &texture, string nazwa, string parametry, int type)
    {
        sprite.setTexture(texture);
        sprite.setPosition((float)x,(float)y);
        sprite.setTextureRect(sf::IntRect(0,0,width,height));
        this->nazwa = nazwa;
        this->parametry = parametry;
        this->type = type;
    }
};

#endif // OBIEKT_HPP
