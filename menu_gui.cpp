#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include "menu_gui.hpp"

Button::Button(sf::Text& text, sf::RectangleShape& shape, std::string& message)
{
    this->text = text;
    this->shape = shape;
    this->message = message;
}

void GuiMenu::start(sf::RenderWindow& window)
{//
    srand(time(NULL));
    authors = false;
    std::string msg[] = {"new_game", "continue", "authors", "exit","donate"};
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(200,50));
    shape.setOutlineThickness(3);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(200,200,200,20));
    font.loadFromFile("data\\text\\arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(25);
    std::string tmp;

    std::fstream file;
    file.open("data\\text\\menu.dat",std::ios::in);
    //wczytanie 4 guzikow glownego menu
    for(int i = 0; i<4; i++)
    {
        getline(file,tmp);
        shape.setPosition(sf::Vector2f(window.getSize().x / 2 - shape.getSize().x / 2,
                                       (window.getSize().y / 2 - 145) + 80*i));
        text.setString(tmp);
        text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2,
                         shape.getPosition().y + text.getGlobalBounds().height / 2);

//        if(i=0)text.move(5,0);
        buttons.push_back(Button(text,shape,msg[i]));
    }
    //guzik donate
    text.setString("Donate");
    if((std::rand()%100)<2)text.setString("Give Me Your Money!!!");
    shape.setSize(sf::Vector2f(text.getGlobalBounds().width + 10,45));
    shape.setPosition(10,window.getSize().y-10-shape.getGlobalBounds().height);
    text.setFillColor(sf::Color::Green);
    text.setPosition(shape.getGlobalBounds().left + 5,shape.getGlobalBounds().top+5);
    buttons.push_back(Button(text,shape,msg[4]));
    //    ///\\\

    //guzik sluzacy jako pole z informacja o tworcach
    shape.setSize(sf::Vector2f(250,500));
    text.setFillColor(sf::Color::Black);
    shape.setPosition(sf::Vector2f((window.getSize().x / 2 - shape.getSize().x / 2),
                                (window.getSize().y / 2 - shape.getSize().y / 2)));
    shape.setFillColor(sf::Color(200,200,200,240));
    text.setString("Rafa³ \"Knitek\" Kurc\nSFML-2.4.1\nGame version 1.0");
    text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2,
                         shape.getPosition().y + shape.getSize().y / 2 - text.getGlobalBounds().height / 2);
    buttons.push_back(Button(text,shape,msg[2]));
    file.close();

    //pobranie adresu donate z pliku
    file.open("data\\text\\odssre.odssre",std::ios::in);
    file>>addres;
    file.close();

}

void GuiMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for(unsigned int i=0;i<buttons.size()-1; i++)
    {
        target.draw(buttons[i].shape);
        target.draw(buttons[i].text);
    }
    if(authors)
    {
        target.draw(buttons[buttons.size()-1].shape);
        target.draw(buttons[buttons.size()-1].text);
    }

}

std::string GuiMenu::check(const sf::Vector2f& mousePos)
{
    for(unsigned int i=0; i<buttons.size()-1; i++)
    {
        if(buttons[i].shape.getGlobalBounds().contains(mousePos))
        {
            buttons[i].shape.setFillColor(sf::Color(200,200,200,200));
            return buttons[i].message;
        }
        else
        {
            buttons[i].shape.setFillColor(sf::Color(200,200,200,20));
        }
    }
    return "gowno";
}
