#ifndef GAME_GUI_HPP
#define GAME_GUI_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "monster_manager.hpp"
#include "texture_manager.hpp"

class GameGui
{
public:
    MonsterManager *monsterManager;
    sf::Sprite backgr;
    sf::Font font;
    sf::Text levelTXT, opponentsTXT, levelNumber, opponentsNumber, timer;
    float time;
    GameGui()
    {

    }
    void load(unsigned int levelnumber,MonsterManager *monsterManager, TextureManager &texmgr);
    void update(float dt);
    void draw(sf::RenderWindow &window);

};

#endif // GAME_GUI_HPP
