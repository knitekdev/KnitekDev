#include "Testing_Tool.hpp"
Testing_Tool::Testing_Tool()
{

}

Testing_Tool::Testing_Tool(sf::Font &font)
{
    this->font = font;
    for(int i =0;i<tools_length;i++)
    {
        texts[i].setFont(font);
        texts[i].setCharacterSize(20);
        texts[i].setPosition(5,(i*30)+30);
    }
    headers[0] = "Player: ";
    headers[1] = "LevelMap: ";
    headers[2] = "MonsterManager: ";
    //ctor
}

void Testing_Tool::update(std::string tab[tools_length])
{
    for(int i = 0;i<tools_length;i++)
    {
        texts[i].setString(headers[i]+tab[i]);
    }
}

void Testing_Tool::draw(sf::RenderWindow& window)
{
    for(int i =0;i<tools_length;i++)
    {
        window.draw(texts[i]);
    }
}



Testing_Tool::~Testing_Tool()
{
    //dtor
}
