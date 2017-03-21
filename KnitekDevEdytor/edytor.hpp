#ifndef EDYTOR_HPP
#define EDYTOR_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "texture_manager.hpp"
#include "obiekt.hpp"

using namespace std;

class Edytor
{
public:
    vector<Obiekt> mapa;
    vector<Obiekt> paleta;
    Obiekt pusty;
    Obiekt* wskazywanyobiekt;
    TextureManager texmgr;
    int nr;
    sf::RenderWindow window;
    sf::View edytorView;
    bool edit;
    unsigned int editnumber;
    unsigned int ruszanyobiekt;

    void run(int nr);
    void draw();
    void loadtextures();
    void wczytajpoziom();
    void zapiszpoziom();
    void wczytajpalete();
    void zlap(sf::Vector2f mousePos);
    void wyrownajpos();
    bool wyszukajwpalecie(Obiekt& obj,string nazwa);
};



#endif // EDYTOR_HPP
