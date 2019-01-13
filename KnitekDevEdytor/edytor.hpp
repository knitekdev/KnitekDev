#ifndef EDYTOR_HPP
#define EDYTOR_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "texture_manager.hpp"
#include "obiekt.hpp"
#include "Palette.hpp"

using namespace std;

class Edytor
{
public:
    vector<Obiekt> mapa;
    vector<Obiekt> paleta;

    Palette palette;

    Obiekt tmpObject;
    Obiekt pusty;
    Obiekt* wskazywanyobiekt;
    TextureManager texmgr;
    int nr;
    sf::RenderWindow window;
    sf::View edytorView;
    bool edit;
    bool moveRight;
    bool moveLeft;
    unsigned int editnumber;
    unsigned int ruszanyobiekt;

    void run(int nr);

    void loadtextures();
    void wczytajpoziom();
    void wczytajpalete();

    void editorLoop();
    void handleInput();
    void update(float dt);
    void draw(float dt);

    void zlap(sf::Vector2f mousePos);
    void wyrownajpos();
    bool wyszukajwpalecie(Obiekt& obj,string nazwa);

    void zapiszpoziom();
};



#endif // EDYTOR_HPP
