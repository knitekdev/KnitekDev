#include "game_gui.hpp"

void GameGui::load(unsigned int levelnumber, MonsterManager* monsterManager, TextureManager &texmgr)
{
    this->monsterManager = monsterManager;
    std::fstream plik;
    plik.open("data\\text\\gamegui.dat",std::ios::in);
    std::string nazwa,name;
    int x,y,charsize;
    plik>>nazwa;
    font.loadFromFile("data\\text\\"+nazwa+".ttf");
    plik>>x; plik>>y; plik>>nazwa;
    backgr.setTexture(texmgr.getRef(nazwa));
    backgr.setPosition(x,y);
    plik>>x; plik>>y; plik>>charsize; plik>>nazwa;
    levelTXT.setFont(font);
    levelTXT.setString(nazwa);
    levelTXT.setCharacterSize(charsize);
    levelTXT.setFillColor(sf::Color::Black);
    levelTXT.setPosition(x,y);
    plik>>x; plik>>y; plik>>charsize; plik>>nazwa;
    opponentsTXT.setFont(font);
    opponentsTXT.setString(nazwa);
    opponentsTXT.setCharacterSize(charsize);
    opponentsTXT.setFillColor(sf::Color::Black);
    opponentsTXT.setPosition(x,y);
    plik>>x; plik>>y; plik>>charsize;
    levelNumber.setFont(font);
    levelNumber.setString(std::to_string(levelnumber));
    levelNumber.setCharacterSize(charsize);
    levelNumber.setFillColor(sf::Color::Black);
    levelNumber.setPosition(x,y);
    plik>>x; plik>>y; plik>>charsize;
    opponentsNumber.setFont(font);
    opponentsNumber.setString(std::to_string(this->monsterManager->monsters.size()));
    opponentsNumber.setCharacterSize(charsize);
    opponentsNumber.setFillColor(sf::Color::Black);
    opponentsNumber.setPosition(x,y);
}

void GameGui::update(float dt)
{
    opponentsNumber.setString(std::to_string(this->monsterManager->monsters.size()));
}

void GameGui::draw(sf::RenderWindow& window)
{
    window.draw(backgr);
    window.draw(levelTXT);
    window.draw(levelNumber);
    window.draw(opponentsNumber);
    window.draw(opponentsTXT);
}
