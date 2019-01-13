#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "texture_manager.hpp"
#include "obiekt.hpp"

class Palette
{
    public:
        Palette();
        Palette(int,TextureManager&);
        virtual ~Palette();

        void MoveDown();
        void MoveUp();

        void ChangeState();
        void Update(float);
        void Draw(sf::RenderWindow&);
        Obiekt GetObjectRef(int);

        std::vector<Obiekt> GetObjectList() { return _objectList; }
        void SetObjectList(std::vector<Obiekt> val) { _objectList = val; }
    protected:

    private:
        unsigned int firstObject;
        unsigned int lastFirstObject;
        sf::View paletteView;
        std::vector<Obiekt> _objectList;
        sf::RectangleShape backgroundShape;
        bool isActive;
        void LoadLevel(int,TextureManager&);
};

#endif // PALETTE_HPP
