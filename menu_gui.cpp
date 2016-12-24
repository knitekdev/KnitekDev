#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>

#include "menu_gui.hpp"

Button::Button(sf::Text& text, sf::RectangleShape& shape, std::string& message)
{
    this->text = text;
    this->shape = shape;
    this->message = message;
}

void GuiMenu::start(sf::RenderWindow& window)
{
    authors = false;
    std::string msg[] = {"new_game", "load_game", "authors", "exit"};
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
    for(int i = 0; i<4; i++)
    {
        getline(file,tmp);
        shape.setPosition(sf::Vector2f(window.getSize().x / 2 - shape.getSize().x / 2,
                                       (window.getSize().y / 2 - 145) + 80*i));
        text.setString(tmp);
        text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2,
                         shape.getPosition().y + text.getGlobalBounds().height / 2);
        buttons.push_back(Button(text,shape,msg[i]));
    }
    shape.setSize(sf::Vector2f(250,500));
    shape.setPosition(sf::Vector2f((window.getSize().x / 2 - shape.getSize().x / 2),
                                (window.getSize().y / 2 - shape.getSize().y / 2)));
    shape.setFillColor(sf::Color(200,200,200,240));
    text.setString("Rafa� \"Knitek\" Kurc\nSFML-2.4.1");
    text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2,
                         shape.getPosition().y + shape.getSize().y / 2 - text.getGlobalBounds().height / 2);
    buttons.push_back(Button(text,shape,msg[2]));


}

void GuiMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for(int i=0;i<4; i++)
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

std::string GuiMenu::check(const sf::Vector2f mousePos)
{
    for(int i=0; i<4; i++)
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
}
